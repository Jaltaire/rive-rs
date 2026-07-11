//! Bindings to the Rive Renderer's native Metal backend.
//!
//! This module drives Rive's pixel local storage renderer directly on Metal
//! instead of going through an abstract [`crate::renderer::Renderer`]
//! implementation. All GPU handles cross the FFI boundary as raw pointers to
//! Metal objects, so every function that accepts one is unsafe and documents
//! the pointer it expects.

use alloc::sync::Arc;
use core::{ffi::c_void, fmt, ptr::NonNull, time::Duration};

use crate::{file::Error, instantiate::Handle};

mod ffi {
    use core::ffi::c_void;

    #[repr(C)]
    pub struct RawMetalContext {
        _private: [u8; 0],
    }

    #[repr(C)]
    pub struct RawRenderTarget {
        _private: [u8; 0],
    }

    #[repr(C)]
    pub struct RawFile {
        _private: [u8; 0],
    }

    #[repr(C)]
    pub struct RawArtboard {
        _private: [u8; 0],
    }

    #[repr(C)]
    pub struct RawStateMachine {
        _private: [u8; 0],
    }

    #[repr(C)]
    pub struct RawBool {
        _private: [u8; 0],
    }

    #[repr(C)]
    pub struct RawNumber {
        _private: [u8; 0],
    }

    #[repr(C)]
    pub struct RawTrigger {
        _private: [u8; 0],
    }

    #[repr(i32)]
    #[derive(Clone, Copy, Debug, Eq, PartialEq)]
    pub enum ImportResult {
        Success,
        #[allow(dead_code)]
        UnsupportedVersion,
        #[allow(dead_code)]
        Malformed,
    }

    extern "C" {
        pub fn rive_rs_metal_context_new(mtl_device: *mut c_void) -> *mut RawMetalContext;
        pub fn rive_rs_metal_context_release(context: *mut RawMetalContext);
        pub fn rive_rs_metal_render_target_new(
            context: *mut RawMetalContext,
            pixel_format: u32,
            width: u32,
            height: u32,
        ) -> *mut RawRenderTarget;
        pub fn rive_rs_metal_render_target_release(render_target: *mut RawRenderTarget);
        pub fn rive_rs_metal_render_target_set_texture(
            render_target: *mut RawRenderTarget,
            mtl_texture: *mut c_void,
        );
        pub fn rive_rs_metal_file_new(
            context: *mut RawMetalContext,
            data: *const u8,
            len: usize,
            result: *mut ImportResult,
        ) -> *const RawFile;
        pub fn rive_rs_metal_file_release(file: *const RawFile);
        pub fn rive_rs_metal_file_artboard_count(file: *const RawFile) -> usize;
        pub fn rive_rs_metal_instantiate_artboard(
            file: *const RawFile,
            index: *const usize,
            artboard_instance: *mut *mut RawArtboard,
        );
        pub fn rive_rs_metal_instantiate_artboard_by_name(
            file: *const RawFile,
            data: *const u8,
            len: usize,
            artboard_instance: *mut *mut RawArtboard,
        );
        pub fn rive_rs_metal_artboard_release(artboard_instance: *const RawArtboard);
        pub fn rive_rs_metal_artboard_width(artboard_instance: *const RawArtboard) -> f32;
        pub fn rive_rs_metal_artboard_height(artboard_instance: *const RawArtboard) -> f32;
        pub fn rive_rs_metal_instantiate_state_machine(
            artboard_instance: *mut RawArtboard,
            index: *const usize,
            state_machine: *mut *mut RawStateMachine,
        );
        pub fn rive_rs_metal_instantiate_state_machine_by_name(
            artboard_instance: *mut RawArtboard,
            data: *const u8,
            len: usize,
            state_machine: *mut *mut RawStateMachine,
        );
        pub fn rive_rs_metal_state_machine_release(state_machine: *const RawStateMachine);
        pub fn rive_rs_metal_state_machine_advance_and_apply(
            state_machine: *mut RawStateMachine,
            elapsed: f32,
        ) -> bool;
        pub fn rive_rs_metal_state_machine_pointer_down(
            state_machine: *mut RawStateMachine,
            x: f32,
            y: f32,
        );
        pub fn rive_rs_metal_state_machine_pointer_move(
            state_machine: *mut RawStateMachine,
            x: f32,
            y: f32,
        );
        pub fn rive_rs_metal_state_machine_pointer_up(
            state_machine: *mut RawStateMachine,
            x: f32,
            y: f32,
        );
        pub fn rive_rs_metal_state_machine_get_bool(
            state_machine: *const RawStateMachine,
            name: *const u8,
            len: usize,
        ) -> *mut RawBool;
        pub fn rive_rs_metal_state_machine_get_number(
            state_machine: *const RawStateMachine,
            name: *const u8,
            len: usize,
        ) -> *mut RawNumber;
        pub fn rive_rs_metal_state_machine_get_trigger(
            state_machine: *const RawStateMachine,
            name: *const u8,
            len: usize,
        ) -> *mut RawTrigger;
        pub fn rive_rs_metal_bool_get(smi_bool: *const RawBool) -> bool;
        pub fn rive_rs_metal_bool_set(smi_bool: *mut RawBool, value: bool);
        pub fn rive_rs_metal_number_get(smi_number: *const RawNumber) -> f32;
        pub fn rive_rs_metal_number_set(smi_number: *mut RawNumber, value: f32);
        pub fn rive_rs_metal_trigger_fire(smi_trigger: *mut RawTrigger);
        pub fn rive_rs_metal_begin_frame(
            context: *mut RawMetalContext,
            width: u32,
            height: u32,
            load_action: super::LoadAction,
            clear_color: u32,
        );
        pub fn rive_rs_metal_draw_artboard(
            context: *mut RawMetalContext,
            artboard_instance: *mut RawArtboard,
            fit: super::Fit,
            alignment_x: f32,
            alignment_y: f32,
            scale_factor: f32,
        );
        pub fn rive_rs_metal_draw_artboard_with_transform(
            context: *mut RawMetalContext,
            artboard_instance: *mut RawArtboard,
            transform: *const f32,
        );
        pub fn rive_rs_metal_flush(
            context: *mut RawMetalContext,
            render_target: *mut RawRenderTarget,
            mtl_command_buffer: *mut c_void,
        );
    }
}

/// Mirrors `rive::Fit` from the C++ runtime.
#[repr(u8)]
#[derive(Clone, Copy, Debug, Default, Eq, PartialEq)]
pub enum Fit {
    Fill,
    #[default]
    Contain,
    Cover,
    FitWidth,
    FitHeight,
    None,
    ScaleDown,
    Layout,
}

/// Mirrors `rive::gpu::LoadAction` from the Rive Renderer.
#[repr(i32)]
#[derive(Clone, Copy, Debug, Default, Eq, PartialEq)]
pub enum LoadAction {
    #[default]
    Clear,
    PreserveRenderTarget,
    DontCare,
}

/// Mirrors `rive::Alignment` from the C++ runtime, where both axes range from
/// -1.0 (top/left) to 1.0 (bottom/right).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Alignment {
    pub x: f32,
    pub y: f32,
}

impl Alignment {
    pub const TOP_LEFT: Self = Self { x: -1.0, y: -1.0 };
    pub const TOP_CENTER: Self = Self { x: 0.0, y: -1.0 };
    pub const TOP_RIGHT: Self = Self { x: 1.0, y: -1.0 };
    pub const CENTER_LEFT: Self = Self { x: -1.0, y: 0.0 };
    pub const CENTER: Self = Self { x: 0.0, y: 0.0 };
    pub const CENTER_RIGHT: Self = Self { x: 1.0, y: 0.0 };
    pub const BOTTOM_LEFT: Self = Self { x: -1.0, y: 1.0 };
    pub const BOTTOM_CENTER: Self = Self { x: 0.0, y: 1.0 };
    pub const BOTTOM_RIGHT: Self = Self { x: 1.0, y: 1.0 };
}

impl Default for Alignment {
    fn default() -> Self {
        Self::CENTER
    }
}

struct ContextInner {
    raw: NonNull<ffi::RawMetalContext>,
}

impl Drop for ContextInner {
    fn drop(&mut self) {
        unsafe {
            ffi::rive_rs_metal_context_release(self.raw.as_ptr());
        }
    }
}

/// The context wraps Metal objects that may be released on any thread, but its
/// rendering methods are not synchronized; the caller must not use one context
/// from multiple threads concurrently.
unsafe impl Send for ContextInner {}
unsafe impl Sync for ContextInner {}

/// A native Rive Renderer bound to a Metal device.
///
/// The context doubles as the [`rive::Factory`] used to import files, so every
/// [`MetalFile`] keeps its originating context alive.
pub struct MetalContext {
    inner: Arc<ContextInner>,
}

impl MetalContext {
    /// Creates a render context for the given Metal device.
    ///
    /// # Safety
    ///
    /// `mtl_device` must be a valid `id<MTLDevice>` pointer. The device is
    /// retained by the context, so the caller only needs to keep it alive for
    /// the duration of this call.
    pub unsafe fn new(mtl_device: *mut c_void) -> Option<Self> {
        NonNull::new(ffi::rive_rs_metal_context_new(mtl_device)).map(|raw| Self {
            inner: Arc::new(ContextInner { raw }),
        })
    }

    /// Creates a render target with the given `MTLPixelFormat` raw value and
    /// dimensions. A texture must be attached with
    /// [`MetalRenderTarget::set_target_texture`] before flushing.
    pub fn make_render_target(
        &self,
        pixel_format: u32,
        width: u32,
        height: u32,
    ) -> MetalRenderTarget {
        let raw = unsafe {
            ffi::rive_rs_metal_render_target_new(
                self.inner.raw.as_ptr(),
                pixel_format,
                width,
                height,
            )
        };

        MetalRenderTarget {
            raw: NonNull::new(raw)
                .expect("The Rive Renderer failed to allocate a Metal render target."),
            width,
            height,
            _context: Arc::clone(&self.inner),
        }
    }

    /// Imports a Rive file using the context's native factory, so all render
    /// objects inside it are backed by the Rive Renderer.
    pub fn import_file(&self, data: &[u8]) -> Result<MetalFile, Error> {
        let mut result = ffi::ImportResult::Success;
        let raw = unsafe {
            ffi::rive_rs_metal_file_new(
                self.inner.raw.as_ptr(),
                data.as_ptr(),
                data.len(),
                &mut result,
            )
        };

        match result {
            ffi::ImportResult::Success => Ok(MetalFile {
                inner: Arc::new(FileInner {
                    raw: NonNull::new(raw.cast_mut())
                        .expect("The Rive file import reported success but returned no file."),
                    _context: Arc::clone(&self.inner),
                }),
            }),
            ffi::ImportResult::UnsupportedVersion => Err(Error::UnsupportedVersion),
            ffi::ImportResult::Malformed => Err(Error::Malformed),
        }
    }

    /// Begins a frame that renders into a target of the given dimensions. All
    /// draws must happen between this call and [`MetalContext::flush`].
    pub fn begin_frame(&mut self, width: u32, height: u32, load_action: LoadAction, clear_color: u32) {
        unsafe {
            ffi::rive_rs_metal_begin_frame(
                self.inner.raw.as_ptr(),
                width,
                height,
                load_action,
                clear_color,
            );
        }
    }

    /// Draws an artboard aligned within the current frame's bounds.
    pub fn draw_artboard(
        &mut self,
        artboard: &MetalArtboard,
        fit: Fit,
        alignment: Alignment,
        scale_factor: f32,
    ) {
        unsafe {
            ffi::rive_rs_metal_draw_artboard(
                self.inner.raw.as_ptr(),
                artboard.inner.raw.as_ptr(),
                fit,
                alignment.x,
                alignment.y,
                scale_factor,
            );
        }
    }

    /// Draws an artboard with an explicit 2x3 column-major transform.
    pub fn draw_artboard_with_transform(&mut self, artboard: &MetalArtboard, transform: &[f32; 6]) {
        unsafe {
            ffi::rive_rs_metal_draw_artboard_with_transform(
                self.inner.raw.as_ptr(),
                artboard.inner.raw.as_ptr(),
                transform.as_ptr(),
            );
        }
    }

    /// Submits the frame's GPU commands.
    ///
    /// # Safety
    ///
    /// `mtl_command_buffer` must be a valid `id<MTLCommandBuffer>` pointer
    /// created from the same Metal device as this context, and the render
    /// target must have a target texture attached whose dimensions match the
    /// frame begun with [`MetalContext::begin_frame`]. The caller is
    /// responsible for committing the command buffer afterwards.
    pub unsafe fn flush(&mut self, render_target: &MetalRenderTarget, mtl_command_buffer: *mut c_void) {
        ffi::rive_rs_metal_flush(
            self.inner.raw.as_ptr(),
            render_target.raw.as_ptr(),
            mtl_command_buffer,
        );
    }
}

impl fmt::Debug for MetalContext {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("MetalContext").finish()
    }
}

/// A Rive Renderer render target backed by a Metal texture.
pub struct MetalRenderTarget {
    raw: NonNull<ffi::RawRenderTarget>,
    width: u32,
    height: u32,
    _context: Arc<ContextInner>,
}

impl MetalRenderTarget {
    /// Attaches the Metal texture that flushes will render into.
    ///
    /// # Safety
    ///
    /// `mtl_texture` must be a valid `id<MTLTexture>` pointer whose usage
    /// includes `MTLTextureUsageRenderTarget` and whose pixel format and
    /// dimensions match the values this render target was created with. The
    /// texture is retained by the render target.
    pub unsafe fn set_target_texture(&mut self, mtl_texture: *mut c_void) {
        ffi::rive_rs_metal_render_target_set_texture(self.raw.as_ptr(), mtl_texture);
    }

    pub fn width(&self) -> u32 {
        self.width
    }

    pub fn height(&self) -> u32 {
        self.height
    }
}

impl Drop for MetalRenderTarget {
    fn drop(&mut self) {
        unsafe {
            ffi::rive_rs_metal_render_target_release(self.raw.as_ptr());
        }
    }
}

unsafe impl Send for MetalRenderTarget {}

impl fmt::Debug for MetalRenderTarget {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("MetalRenderTarget")
            .field("width", &self.width)
            .field("height", &self.height)
            .finish()
    }
}

struct FileInner {
    raw: NonNull<ffi::RawFile>,
    _context: Arc<ContextInner>,
}

impl Drop for FileInner {
    fn drop(&mut self) {
        unsafe {
            ffi::rive_rs_metal_file_release(self.raw.as_ptr());
        }
    }
}

unsafe impl Send for FileInner {}
unsafe impl Sync for FileInner {}

/// A Rive file imported through a [`MetalContext`].
pub struct MetalFile {
    inner: Arc<FileInner>,
}

impl MetalFile {
    pub fn artboard_count(&self) -> usize {
        unsafe { ffi::rive_rs_metal_file_artboard_count(self.inner.raw.as_ptr()) }
    }

    pub fn instantiate_artboard(&self, handle: Handle) -> Option<MetalArtboard> {
        let mut raw = core::ptr::null_mut();

        unsafe {
            match handle {
                Handle::Default => {
                    ffi::rive_rs_metal_instantiate_artboard(
                        self.inner.raw.as_ptr(),
                        core::ptr::null(),
                        &mut raw,
                    );
                }
                Handle::Index(index) => {
                    ffi::rive_rs_metal_instantiate_artboard(
                        self.inner.raw.as_ptr(),
                        &index,
                        &mut raw,
                    );
                }
                Handle::Name(name) => {
                    ffi::rive_rs_metal_instantiate_artboard_by_name(
                        self.inner.raw.as_ptr(),
                        name.as_ptr(),
                        name.len(),
                        &mut raw,
                    );
                }
            }
        }

        NonNull::new(raw).map(|raw| MetalArtboard {
            inner: Arc::new(ArtboardInner {
                raw,
                _file: Arc::clone(&self.inner),
            }),
        })
    }
}

impl fmt::Debug for MetalFile {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("MetalFile").finish()
    }
}

struct ArtboardInner {
    raw: NonNull<ffi::RawArtboard>,
    _file: Arc<FileInner>,
}

impl Drop for ArtboardInner {
    fn drop(&mut self) {
        unsafe {
            ffi::rive_rs_metal_artboard_release(self.raw.as_ptr());
        }
    }
}

unsafe impl Send for ArtboardInner {}
unsafe impl Sync for ArtboardInner {}

/// An artboard instance whose render objects are backed by the Rive Renderer.
pub struct MetalArtboard {
    inner: Arc<ArtboardInner>,
}

impl MetalArtboard {
    pub fn width(&self) -> f32 {
        unsafe { ffi::rive_rs_metal_artboard_width(self.inner.raw.as_ptr()) }
    }

    pub fn height(&self) -> f32 {
        unsafe { ffi::rive_rs_metal_artboard_height(self.inner.raw.as_ptr()) }
    }

    pub fn instantiate_state_machine(&self, handle: Handle) -> Option<MetalStateMachine> {
        let mut raw = core::ptr::null_mut();

        unsafe {
            match handle {
                Handle::Default => {
                    ffi::rive_rs_metal_instantiate_state_machine(
                        self.inner.raw.as_ptr(),
                        core::ptr::null(),
                        &mut raw,
                    );
                }
                Handle::Index(index) => {
                    ffi::rive_rs_metal_instantiate_state_machine(
                        self.inner.raw.as_ptr(),
                        &index,
                        &mut raw,
                    );
                }
                Handle::Name(name) => {
                    ffi::rive_rs_metal_instantiate_state_machine_by_name(
                        self.inner.raw.as_ptr(),
                        name.as_ptr(),
                        name.len(),
                        &mut raw,
                    );
                }
            }
        }

        NonNull::new(raw).map(|raw| MetalStateMachine {
            raw,
            _artboard: Arc::clone(&self.inner),
        })
    }
}

impl fmt::Debug for MetalArtboard {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("MetalArtboard").finish()
    }
}

/// A state machine instance driving a [`MetalArtboard`].
pub struct MetalStateMachine {
    raw: NonNull<ffi::RawStateMachine>,
    _artboard: Arc<ArtboardInner>,
}

impl MetalStateMachine {
    pub fn advance_and_apply(&mut self, elapsed: Duration) -> bool {
        unsafe {
            ffi::rive_rs_metal_state_machine_advance_and_apply(
                self.raw.as_ptr(),
                elapsed.as_secs_f32(),
            )
        }
    }

    pub fn pointer_down(&mut self, x: f32, y: f32) {
        unsafe {
            ffi::rive_rs_metal_state_machine_pointer_down(self.raw.as_ptr(), x, y);
        }
    }

    pub fn pointer_move(&mut self, x: f32, y: f32) {
        unsafe {
            ffi::rive_rs_metal_state_machine_pointer_move(self.raw.as_ptr(), x, y);
        }
    }

    pub fn pointer_up(&mut self, x: f32, y: f32) {
        unsafe {
            ffi::rive_rs_metal_state_machine_pointer_up(self.raw.as_ptr(), x, y);
        }
    }

    pub fn get_bool(&self, name: &str) -> Option<bool> {
        unsafe {
            let raw =
                ffi::rive_rs_metal_state_machine_get_bool(self.raw.as_ptr(), name.as_ptr(), name.len());
            (!raw.is_null()).then(|| ffi::rive_rs_metal_bool_get(raw))
        }
    }

    pub fn set_bool(&mut self, name: &str, value: bool) -> bool {
        unsafe {
            let raw =
                ffi::rive_rs_metal_state_machine_get_bool(self.raw.as_ptr(), name.as_ptr(), name.len());
            if raw.is_null() {
                return false;
            }
            ffi::rive_rs_metal_bool_set(raw, value);
            true
        }
    }

    pub fn get_number(&self, name: &str) -> Option<f32> {
        unsafe {
            let raw = ffi::rive_rs_metal_state_machine_get_number(
                self.raw.as_ptr(),
                name.as_ptr(),
                name.len(),
            );
            (!raw.is_null()).then(|| ffi::rive_rs_metal_number_get(raw))
        }
    }

    pub fn set_number(&mut self, name: &str, value: f32) -> bool {
        unsafe {
            let raw = ffi::rive_rs_metal_state_machine_get_number(
                self.raw.as_ptr(),
                name.as_ptr(),
                name.len(),
            );
            if raw.is_null() {
                return false;
            }
            ffi::rive_rs_metal_number_set(raw, value);
            true
        }
    }

    pub fn fire_trigger(&mut self, name: &str) -> bool {
        unsafe {
            let raw = ffi::rive_rs_metal_state_machine_get_trigger(
                self.raw.as_ptr(),
                name.as_ptr(),
                name.len(),
            );
            if raw.is_null() {
                return false;
            }
            ffi::rive_rs_metal_trigger_fire(raw);
            true
        }
    }
}

impl Drop for MetalStateMachine {
    fn drop(&mut self) {
        unsafe {
            ffi::rive_rs_metal_state_machine_release(self.raw.as_ptr());
        }
    }
}

unsafe impl Send for MetalStateMachine {}

impl fmt::Debug for MetalStateMachine {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("MetalStateMachine").finish()
    }
}

#[cfg(all(test, target_os = "macos"))]
mod tests {
    use alloc::{borrow::Cow, vec};
    use core::{ffi::c_void, time::Duration};

    use super::{Alignment, Fit, LoadAction, MetalContext};
    use crate::{file::Error, instantiate::Handle};

    extern "C" {
        fn rive_rs_metal_test_default_device() -> *mut c_void;
        fn rive_rs_metal_test_command_queue_new(mtl_device: *mut c_void) -> *mut c_void;
        fn rive_rs_metal_test_command_buffer_new(mtl_command_queue: *mut c_void) -> *mut c_void;
        fn rive_rs_metal_test_command_buffer_commit_and_wait(mtl_command_buffer: *mut c_void);
        fn rive_rs_metal_test_texture_new(
            mtl_device: *mut c_void,
            pixel_format: u32,
            width: u32,
            height: u32,
        ) -> *mut c_void;
        fn rive_rs_metal_test_texture_read(
            mtl_texture: *mut c_void,
            out: *mut u8,
            width: u32,
            height: u32,
        );
        fn rive_rs_metal_test_object_release(object: *mut c_void);
    }

    const MTL_PIXEL_FORMAT_BGRA8_UNORM: u32 = 80;
    const RIV: &[u8] = include_bytes!("../../assets/rating-animation.riv");

    fn context() -> (MetalContext, *mut c_void) {
        let device = unsafe { rive_rs_metal_test_default_device() };
        assert!(
            !device.is_null(),
            "No default Metal device is available on this machine."
        );
        let context = unsafe { MetalContext::new(device) }
            .expect("The Metal render context failed to initialize.");

        (context, device)
    }

    #[test]
    fn import_rejects_malformed_data() {
        let (context, device) = context();

        assert_eq!(
            context.import_file(&[0xDE, 0xAD, 0xBE, 0xEF]).err(),
            Some(Error::Malformed)
        );

        drop(context);
        unsafe {
            rive_rs_metal_test_object_release(device);
        }
    }

    #[test]
    fn import_succeeds_and_exposes_artboards() {
        let (context, device) = context();

        let file = context
            .import_file(RIV)
            .expect("The test asset failed to import.");
        assert!(file.artboard_count() >= 1);

        assert!(file
            .instantiate_artboard(Handle::Name(Cow::Borrowed("no-such-artboard")))
            .is_none());

        let artboard = file
            .instantiate_artboard(Handle::Default)
            .expect("The default artboard failed to instantiate.");
        assert!(artboard.width() > 0.0);
        assert!(artboard.height() > 0.0);

        drop(artboard);
        drop(file);
        drop(context);
        unsafe {
            rive_rs_metal_test_object_release(device);
        }
    }

    #[test]
    fn state_machine_inputs_round_trip() {
        let (context, device) = context();

        let file = context
            .import_file(RIV)
            .expect("The test asset failed to import.");
        let artboard = file
            .instantiate_artboard(Handle::Default)
            .expect("The default artboard failed to instantiate.");
        let mut state_machine = artboard
            .instantiate_state_machine(Handle::Default)
            .expect("The default state machine failed to instantiate.");

        assert!(state_machine.get_number("rating").is_some());
        assert!(state_machine.set_number("rating", 5.0));
        assert_eq!(state_machine.get_number("rating"), Some(5.0));

        assert!(state_machine.get_number("no-such-input").is_none());
        assert!(!state_machine.set_number("no-such-input", 1.0));
        assert!(state_machine.get_bool("no-such-input").is_none());
        assert!(!state_machine.set_bool("no-such-input", true));
        assert!(!state_machine.fire_trigger("no-such-input"));

        state_machine.advance_and_apply(Duration::from_millis(16));

        drop(state_machine);
        drop(artboard);
        drop(file);
        drop(context);
        unsafe {
            rive_rs_metal_test_object_release(device);
        }
    }

    #[test]
    fn renders_an_artboard_into_a_metal_texture() {
        const WIDTH: u32 = 256;
        const HEIGHT: u32 = 256;
        const CLEAR_COLOR_ARGB: u32 = 0xFF00_00FF;
        const CLEAR_COLOR_BGRA_BYTES: [u8; 4] = [0xFF, 0x00, 0x00, 0xFF];

        let (mut context, device) = context();

        let file = context
            .import_file(RIV)
            .expect("The test asset failed to import.");
        let artboard = file
            .instantiate_artboard(Handle::Default)
            .expect("The default artboard failed to instantiate.");
        let mut state_machine = artboard
            .instantiate_state_machine(Handle::Default)
            .expect("The default state machine failed to instantiate.");
        state_machine.advance_and_apply(Duration::from_millis(16));

        let mut render_target =
            context.make_render_target(MTL_PIXEL_FORMAT_BGRA8_UNORM, WIDTH, HEIGHT);
        assert_eq!(render_target.width(), WIDTH);
        assert_eq!(render_target.height(), HEIGHT);

        let texture =
            unsafe { rive_rs_metal_test_texture_new(device, MTL_PIXEL_FORMAT_BGRA8_UNORM, WIDTH, HEIGHT) };
        assert!(!texture.is_null());
        unsafe {
            render_target.set_target_texture(texture);
        }

        context.begin_frame(WIDTH, HEIGHT, LoadAction::Clear, CLEAR_COLOR_ARGB);
        context.draw_artboard(&artboard, Fit::Contain, Alignment::CENTER, 1.0);

        let queue = unsafe { rive_rs_metal_test_command_queue_new(device) };
        let command_buffer = unsafe { rive_rs_metal_test_command_buffer_new(queue) };
        unsafe {
            context.flush(&render_target, command_buffer);
            rive_rs_metal_test_command_buffer_commit_and_wait(command_buffer);
        }

        let mut pixels = vec![0_u8; (WIDTH * HEIGHT * 4) as usize];
        unsafe {
            rive_rs_metal_test_texture_read(texture, pixels.as_mut_ptr(), WIDTH, HEIGHT);
        }

        assert!(
            pixels.chunks_exact(4).any(|pixel| pixel != [0, 0, 0, 0]),
            "The flush never wrote to the target texture."
        );
        assert!(
            pixels
                .chunks_exact(4)
                .any(|pixel| pixel != CLEAR_COLOR_BGRA_BYTES),
            "The artboard drew no pixels over the clear color."
        );

        drop(state_machine);
        drop(artboard);
        drop(file);
        drop(render_target);
        drop(context);
        unsafe {
            rive_rs_metal_test_object_release(command_buffer);
            rive_rs_metal_test_object_release(queue);
            rive_rs_metal_test_object_release(texture);
            rive_rs_metal_test_object_release(device);
        }
    }
}
