//! A dependency-free reader for the names of the animations and state machines
//! declared in a Rive (`.riv`) file.
//!
//! Unlike the main `rive-rs` runtime, this crate does not link the Rive C++
//! core; it walks the binary format directly, so it can run at build time (for
//! example inside a procedural macro) without a C++ toolchain.
//!
//! ```no_run
//! let bytes = std::fs::read("character.riv").unwrap();
//! let metadata = rive_metadata::read(&bytes).unwrap();
//! for animation in &metadata.animations {
//!     println!("animation: {animation}");
//! }
//! for state_machine in &metadata.state_machines {
//!     println!("state machine: {state_machine}");
//! }
//! ```

use std::collections::HashMap;
use std::fmt;

mod field_types;
use field_types::KNOWN_FIELD_TYPES;

const FINGERPRINT: [u8; 4] = *b"RIVE";

const LINEAR_ANIMATION_TYPE_KEY: u64 = 31;
const STATE_MACHINE_TYPE_KEY: u64 = 53;
const NAME_PROPERTY_KEY: u64 = 55;

const FIELD_STRING: u8 = 1;
const FIELD_DOUBLE: u8 = 2;
const FIELD_COLOR: u8 = 3;

/// The names of the animations and state machines found in a Rive file, listed
/// in the order they appear. Names may repeat when a file contains more than one
/// artboard.
#[derive(Debug, Clone, PartialEq, Eq, Default)]
pub struct Metadata {
    pub animations: Vec<String>,
    pub state_machines: Vec<String>,
}

/// A failure encountered while reading a Rive file's metadata.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Error {
    /// The buffer does not begin with the `RIVE` fingerprint.
    NotARiveFile,
    /// The buffer ended in the middle of a value.
    UnexpectedEof,
    /// A property was encountered whose type is not described by the file's
    /// table of contents, so its value cannot be skipped.
    UnknownProperty { property_key: u64 },
    /// A name was not valid UTF-8.
    InvalidName,
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Error::NotARiveFile => write!(f, "The buffer is not a Rive file."),
            Error::UnexpectedEof => write!(f, "The Rive file ended unexpectedly."),
            Error::UnknownProperty { property_key } => write!(
                f,
                "The Rive file uses property {property_key}, which is missing from its table of contents."
            ),
            Error::InvalidName => write!(f, "A name in the Rive file was not valid UTF-8."),
        }
    }
}

impl std::error::Error for Error {}

struct Reader<'a> {
    bytes: &'a [u8],
    position: usize,
}

impl<'a> Reader<'a> {
    fn new(bytes: &'a [u8]) -> Self {
        Reader { bytes, position: 0 }
    }

    fn is_at_end(&self) -> bool {
        self.position >= self.bytes.len()
    }

    fn read_byte(&mut self) -> Result<u8, Error> {
        let byte = *self.bytes.get(self.position).ok_or(Error::UnexpectedEof)?;
        self.position += 1;
        Ok(byte)
    }

    fn read_u32(&mut self) -> Result<u32, Error> {
        let end = self.position.checked_add(4).ok_or(Error::UnexpectedEof)?;
        let slice = self
            .bytes
            .get(self.position..end)
            .ok_or(Error::UnexpectedEof)?;
        self.position = end;
        Ok(u32::from_le_bytes([slice[0], slice[1], slice[2], slice[3]]))
    }

    fn read_var_uint(&mut self) -> Result<u64, Error> {
        let mut result: u64 = 0;
        let mut shift: u32 = 0;
        loop {
            let byte = self.read_byte()?;
            result |= u64::from(byte & 0x7f) << shift;
            if byte & 0x80 == 0 {
                return Ok(result);
            }
            shift += 7;
            if shift >= 64 {
                return Err(Error::UnexpectedEof);
            }
        }
    }

    fn read_string(&mut self) -> Result<&'a [u8], Error> {
        let length = usize::try_from(self.read_var_uint()?).map_err(|_| Error::UnexpectedEof)?;
        let end = self
            .position
            .checked_add(length)
            .ok_or(Error::UnexpectedEof)?;
        let slice = self
            .bytes
            .get(self.position..end)
            .ok_or(Error::UnexpectedEof)?;
        self.position = end;
        Ok(slice)
    }

    fn skip(&mut self, count: usize) -> Result<(), Error> {
        let end = self
            .position
            .checked_add(count)
            .ok_or(Error::UnexpectedEof)?;
        if end > self.bytes.len() {
            return Err(Error::UnexpectedEof);
        }
        self.position = end;
        Ok(())
    }
}

fn read_table_of_contents(reader: &mut Reader) -> Result<HashMap<u64, u8>, Error> {
    let mut property_keys = Vec::new();
    loop {
        let property_key = reader.read_var_uint()?;
        if property_key == 0 {
            break;
        }
        property_keys.push(property_key);
    }

    let mut field_types = HashMap::with_capacity(property_keys.len());
    let mut current = 0u32;
    let mut bit = 8u32;
    for property_key in property_keys {
        if bit == 8 {
            current = reader.read_u32()?;
            bit = 0;
        }
        let field_type = ((current >> bit) & 3) as u8;
        field_types.insert(property_key, field_type);
        bit += 2;
    }

    Ok(field_types)
}

fn lookup_field_type(property_key: u64, table_of_contents: &HashMap<u64, u8>) -> Option<u8> {
    if let Ok(key) = u16::try_from(property_key) {
        if let Ok(index) = KNOWN_FIELD_TYPES.binary_search_by_key(&key, |entry| entry.0) {
            return Some(KNOWN_FIELD_TYPES[index].1);
        }
    }
    table_of_contents.get(&property_key).copied()
}

/// Reads the animation and state-machine names from the bytes of a `.riv` file.
pub fn read(bytes: &[u8]) -> Result<Metadata, Error> {
    let mut reader = Reader::new(bytes);

    for expected in FINGERPRINT {
        if reader.read_byte()? != expected {
            return Err(Error::NotARiveFile);
        }
    }

    let _major_version = reader.read_var_uint()?;
    let _minor_version = reader.read_var_uint()?;
    let _file_id = reader.read_var_uint()?;

    let field_types = read_table_of_contents(&mut reader)?;

    let mut metadata = Metadata::default();
    while !reader.is_at_end() {
        let type_key = reader.read_var_uint()?;
        let is_named_target =
            type_key == LINEAR_ANIMATION_TYPE_KEY || type_key == STATE_MACHINE_TYPE_KEY;
        let mut name: Option<String> = None;

        loop {
            let property_key = reader.read_var_uint()?;
            if property_key == 0 {
                break;
            }
            let field_type = lookup_field_type(property_key, &field_types)
                .ok_or(Error::UnknownProperty { property_key })?;
            match field_type {
                FIELD_STRING => {
                    let raw = reader.read_string()?;
                    if property_key == NAME_PROPERTY_KEY && is_named_target {
                        let text = std::str::from_utf8(raw).map_err(|_| Error::InvalidName)?;
                        name = Some(text.to_owned());
                    }
                }
                FIELD_DOUBLE | FIELD_COLOR => reader.skip(4)?,
                _ => {
                    reader.read_var_uint()?;
                }
            }
        }

        if let Some(name) = name {
            if type_key == LINEAR_ANIMATION_TYPE_KEY {
                metadata.animations.push(name);
            } else {
                metadata.state_machines.push(name);
            }
        }
    }

    Ok(metadata)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn push_var_uint(buffer: &mut Vec<u8>, mut value: u64) {
        loop {
            let mut byte = (value & 0x7f) as u8;
            value >>= 7;
            if value != 0 {
                byte |= 0x80;
            }
            buffer.push(byte);
            if value == 0 {
                break;
            }
        }
    }

    fn push_string(buffer: &mut Vec<u8>, text: &str) {
        push_var_uint(buffer, text.len() as u64);
        buffer.extend_from_slice(text.as_bytes());
    }

    struct Builder {
        header: Vec<u8>,
        keys: Vec<(u64, u8)>,
        objects: Vec<u8>,
    }

    enum Value {
        Uint(u64),
        Str(&'static str),
        Double(f32),
        Color(u32),
    }

    impl Builder {
        fn new() -> Self {
            let mut header = Vec::new();
            header.extend_from_slice(b"RIVE");
            push_var_uint(&mut header, 7);
            push_var_uint(&mut header, 0);
            push_var_uint(&mut header, 1234);
            Builder {
                header,
                keys: Vec::new(),
                objects: Vec::new(),
            }
        }

        fn declare(mut self, property_key: u64, field_type: u8) -> Self {
            self.keys.push((property_key, field_type));
            self
        }

        fn object(mut self, type_key: u64, properties: &[(u64, Value)]) -> Self {
            push_var_uint(&mut self.objects, type_key);
            for (property_key, value) in properties {
                push_var_uint(&mut self.objects, *property_key);
                match value {
                    Value::Uint(v) => push_var_uint(&mut self.objects, *v),
                    Value::Str(s) => push_string(&mut self.objects, s),
                    Value::Double(v) => self.objects.extend_from_slice(&v.to_le_bytes()),
                    Value::Color(v) => self.objects.extend_from_slice(&v.to_le_bytes()),
                }
            }
            push_var_uint(&mut self.objects, 0);
            self
        }

        fn build(self) -> Vec<u8> {
            let mut out = self.header;
            for (property_key, _) in &self.keys {
                push_var_uint(&mut out, *property_key);
            }
            push_var_uint(&mut out, 0);

            let mut current = 0u32;
            let mut bit = 0u32;
            for (_, field_type) in &self.keys {
                current |= (u32::from(*field_type) & 3) << bit;
                bit += 2;
                if bit == 8 {
                    out.extend_from_slice(&current.to_le_bytes());
                    current = 0;
                    bit = 0;
                }
            }
            if bit != 0 {
                out.extend_from_slice(&current.to_le_bytes());
            }

            out.extend_from_slice(&self.objects);
            out
        }
    }

    #[test]
    fn reads_animation_and_state_machine_names() {
        let bytes = Builder::new()
            .declare(NAME_PROPERTY_KEY, FIELD_STRING)
            .object(
                LINEAR_ANIMATION_TYPE_KEY,
                &[(NAME_PROPERTY_KEY, Value::Str("Idle"))],
            )
            .object(
                STATE_MACHINE_TYPE_KEY,
                &[(NAME_PROPERTY_KEY, Value::Str("Main"))],
            )
            .object(7, &[(NAME_PROPERTY_KEY, Value::Str("Rectangle"))])
            .build();

        let metadata = read(&bytes).unwrap();
        assert_eq!(metadata.animations, vec!["Idle".to_string()]);
        assert_eq!(metadata.state_machines, vec!["Main".to_string()]);
    }

    #[test]
    fn skips_every_field_type_before_the_name() {
        let bytes = Builder::new()
            .declare(5, 0)
            .declare(NAME_PROPERTY_KEY, FIELD_STRING)
            .declare(13, FIELD_DOUBLE)
            .declare(37, FIELD_COLOR)
            .object(
                LINEAR_ANIMATION_TYPE_KEY,
                &[
                    (5, Value::Uint(999)),
                    (13, Value::Double(1.5)),
                    (37, Value::Color(0xff00ff00)),
                    (NAME_PROPERTY_KEY, Value::Str("Bounce")),
                ],
            )
            .build();

        let metadata = read(&bytes).unwrap();
        assert_eq!(metadata.animations, vec!["Bounce".to_string()]);
        assert!(metadata.state_machines.is_empty());
    }

    #[test]
    fn resolves_known_keys_absent_from_the_table_of_contents() {
        let bytes = Builder::new()
            .declare(NAME_PROPERTY_KEY, FIELD_STRING)
            .object(
                LINEAR_ANIMATION_TYPE_KEY,
                &[
                    (14, Value::Double(3.0)),
                    (NAME_PROPERTY_KEY, Value::Str("Spin")),
                ],
            )
            .build();

        let metadata = read(&bytes).unwrap();
        assert_eq!(metadata.animations, vec!["Spin".to_string()]);
    }

    #[test]
    fn preserves_order_and_duplicates_across_artboards() {
        let bytes = Builder::new()
            .declare(NAME_PROPERTY_KEY, FIELD_STRING)
            .object(
                LINEAR_ANIMATION_TYPE_KEY,
                &[(NAME_PROPERTY_KEY, Value::Str("Walk"))],
            )
            .object(
                LINEAR_ANIMATION_TYPE_KEY,
                &[(NAME_PROPERTY_KEY, Value::Str("Run"))],
            )
            .object(
                LINEAR_ANIMATION_TYPE_KEY,
                &[(NAME_PROPERTY_KEY, Value::Str("Walk"))],
            )
            .build();

        let metadata = read(&bytes).unwrap();
        assert_eq!(
            metadata.animations,
            vec!["Walk".to_string(), "Run".to_string(), "Walk".to_string()]
        );
    }

    #[test]
    fn spans_more_than_one_toc_word() {
        let mut builder = Builder::new();
        for key in 60..70 {
            builder = builder.declare(key, 0);
        }
        let bytes = builder
            .declare(NAME_PROPERTY_KEY, FIELD_STRING)
            .object(
                STATE_MACHINE_TYPE_KEY,
                &[(NAME_PROPERTY_KEY, Value::Str("Flow"))],
            )
            .build();

        let metadata = read(&bytes).unwrap();
        assert_eq!(metadata.state_machines, vec!["Flow".to_string()]);
    }

    #[test]
    fn rejects_a_non_rive_buffer() {
        assert_eq!(read(b"NOPE...."), Err(Error::NotARiveFile));
        assert_eq!(read(b""), Err(Error::UnexpectedEof));
    }

    #[test]
    fn reports_a_truncated_buffer() {
        let mut bytes = Builder::new()
            .declare(NAME_PROPERTY_KEY, FIELD_STRING)
            .object(
                LINEAR_ANIMATION_TYPE_KEY,
                &[(NAME_PROPERTY_KEY, Value::Str("Idle"))],
            )
            .build();
        bytes.truncate(bytes.len() - 2);
        assert_eq!(read(&bytes), Err(Error::UnexpectedEof));
    }
}
