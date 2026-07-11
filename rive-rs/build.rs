use std::{
    env,
    ffi::OsString,
    path::{Path, PathBuf},
};

use walkdir::WalkDir;

const WASM_TARGET: &str = "wasm32-wasip1";

struct WasiSdk {
    root: PathBuf,
    sysroot: PathBuf,
    clang: PathBuf,
    clangxx: PathBuf,
    ar: PathBuf,
}

fn locate_wasi_sdk() -> WasiSdk {
    let root = match env::var_os("WASI_SDK_PATH") {
        Some(path) => PathBuf::from(path),
        None => {
            let Some(home) = env::var_os("HOME") else {
                panic!(
                    "Set WASI_SDK_PATH to your wasi-sdk installation; it is required to build the Rive C++ core for wasm."
                );
            };
            PathBuf::from(home).join("wasi-sdk-33")
        }
    };

    if !root.is_dir() {
        panic!(
            "wasi-sdk was not found at {}. Install it from https://github.com/WebAssembly/wasi-sdk/releases and set WASI_SDK_PATH so the Rive C++ core can be built for wasm.",
            root.display()
        );
    }

    let bin = root.join("bin");
    let sysroot = root.join("share/wasi-sysroot");
    WasiSdk {
        clang: bin.join("clang"),
        clangxx: bin.join("clang++"),
        ar: bin.join("llvm-ar"),
        root,
        sysroot,
    }
}

fn configure_wasm(build: &mut cc::Build, wasi: &WasiSdk, cpp: bool) {
    build
        .compiler(if cpp { &wasi.clangxx } else { &wasi.clang })
        .archiver(&wasi.ar)
        .flag(format!("--target={WASM_TARGET}"))
        .flag(format!("--sysroot={}", wasi.sysroot.display()));

    if cpp {
        build
            .flag("-fno-exceptions")
            .flag("-fno-rtti")
            .cpp_link_stdlib(None);
    }
}

fn find_clang_builtins(wasi_sdk: &Path) -> Option<PathBuf> {
    let clang_root = wasi_sdk.join("lib/clang");
    for entry in std::fs::read_dir(&clang_root).ok()?.flatten() {
        let candidate = entry.path().join("lib/wasm32-unknown-wasip1");
        if candidate.join("libclang_rt.builtins.a").exists() {
            return Some(candidate);
        }
    }
    None
}

fn emit_wasm_link_flags(wasi: &WasiSdk) {
    let libcxx_dir = wasi.sysroot.join("lib/wasm32-wasip1/noeh");
    let libc_dir = wasi.sysroot.join("lib/wasm32-wasip1");

    println!("cargo:rustc-link-search=native={}", libcxx_dir.display());
    println!("cargo:rustc-link-search=native={}", libc_dir.display());

    if let Some(builtins_dir) = find_clang_builtins(&wasi.root) {
        println!("cargo:rustc-link-search=native={}", builtins_dir.display());
        println!("cargo:rustc-link-lib=static=clang_rt.builtins");
    }

    println!("cargo:rustc-link-lib=static=c++");
    println!("cargo:rustc-link-lib=static=c++abi");
    println!("cargo:rustc-link-lib=static=c");
    println!("cargo:rustc-link-lib=static=m");
}

fn all_files_with_extension<P: AsRef<Path>>(
    path: P,
    extension: &str,
) -> impl Iterator<Item = PathBuf> + '_ {
    WalkDir::new(path).into_iter().filter_map(move |entry| {
        entry
            .ok()
            .map(|entry| entry.into_path())
            .filter(|path| path.extension() == Some(&OsString::from(extension)))
    })
}

fn top_level_files_with_extension<P: AsRef<Path>>(
    path: P,
    extension: &str,
) -> impl Iterator<Item = PathBuf> + '_ {
    WalkDir::new(path)
        .max_depth(1)
        .into_iter()
        .filter_map(move |entry| {
            entry
                .ok()
                .map(|entry| entry.into_path())
                .filter(|path| path.extension() == Some(&OsString::from(extension)))
        })
}

fn metal_renderer_platform_define() -> Option<&'static str> {
    let target_os = env::var("CARGO_CFG_TARGET_OS").unwrap();
    let target_abi = env::var("CARGO_CFG_TARGET_ABI").unwrap_or_default();
    let target_arch = env::var("CARGO_CFG_TARGET_ARCH").unwrap();

    match target_os.as_str() {
        "macos" => Some("RIVE_MACOSX"),
        "ios" => {
            if target_abi == "sim" || target_arch == "x86_64" {
                Some("RIVE_IOS_SIMULATOR")
            } else {
                Some("RIVE_IOS")
            }
        }
        _ => None,
    }
}

fn build_metal_renderer(rive_cpp_path: &Path, platform_define: &str) {
    println!("cargo:rerun-if-changed=src/metal_ffi.mm");
    println!("cargo:rerun-if-changed=generated/shaders");

    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let renderer_src = rive_cpp_path.join("renderer/src");

    let mut renderer = cc::Build::new();
    renderer
        .cpp(true)
        .include(rive_cpp_path.join("include"))
        .include(rive_cpp_path.join("renderer/include"))
        .include(&renderer_src)
        .include(&manifest_dir)
        .files(top_level_files_with_extension(&renderer_src, "cpp"))
        .flag("-std=c++17")
        .define(platform_define, None)
        .warnings(false);
    renderer.compile("rive-renderer");

    let mut renderer_metal = cc::Build::new();
    renderer_metal
        .cpp(true)
        .include(rive_cpp_path.join("include"))
        .include(rive_cpp_path.join("renderer/include"))
        .include(&renderer_src)
        .include(&manifest_dir)
        .files(top_level_files_with_extension(
            renderer_src.join("metal"),
            "mm",
        ))
        .file("src/metal_ffi.mm")
        .flag("-std=c++17")
        .flag("-fobjc-arc")
        .define(platform_define, None)
        .warnings(false);
    renderer_metal.compile("rive-renderer-metal");

    println!("cargo:rustc-link-lib=framework=Metal");
    println!("cargo:rustc-link-lib=framework=QuartzCore");
    println!("cargo:rustc-link-lib=framework=Foundation");
}

fn main() {
    println!("cargo:rerun-if-changed=src/ffi.cpp");
    println!("cargo:rerun-if-env-changed=WASI_SDK_PATH");

    let wasm =
        (env::var("CARGO_CFG_TARGET_ARCH").as_deref() == Ok("wasm32")).then(locate_wasi_sdk);

    let metal_platform_define = env::var_os("CARGO_FEATURE_METAL_RENDERER")
        .is_some()
        .then(metal_renderer_platform_define)
        .flatten();
    let cpp_std = if metal_platform_define.is_some() {
        "-std=c++17"
    } else {
        "-std=c++14"
    };

    let rive_cpp_path = env::var("RIVE_CPP_PATH")
        .map(PathBuf::from)
        .unwrap_or_else(|_| PathBuf::from("../submodules/rive-cpp"));

    let mut ffi = cc::Build::new();
    ffi.cpp(true)
        .include(rive_cpp_path.join("include"))
        .file("src/ffi.cpp")
        .flag(cpp_std)
        .warnings(false);
    if let Some(wasi) = &wasm {
        configure_wasm(&mut ffi, wasi, true);
    }
    ffi.compile("rive-ffi");

    if cfg!(feature = "layout") {
        let mut yoga = cc::Build::new();
        yoga.cpp(true)
            .flag("-std=c++11")
            .files(all_files_with_extension("../submodules/yoga/yoga", "cpp"))
            .include("../submodules/yoga")
            .define("YOGA_EXPORT=", None)
            .warnings(false);
        if let Some(wasi) = &wasm {
            configure_wasm(&mut yoga, wasi, true);
        }
        yoga.compile("yoga");
    }

    if cfg!(feature = "text") {
        let target = env::var("TARGET").unwrap();
        let profile = env::var("PROFILE").unwrap();

        let mut cfg = cc::Build::new();
        cfg.cpp(true)
            .flag_if_supported("-std=c++11") // for unix
            .warnings(false)
            .file("../submodules/harfbuzz/src/harfbuzz.cc");

        if !target.contains("windows") {
            cfg.define("HAVE_PTHREAD", "1");
        }

        if target.contains("apple") && profile.contains("release") {
            cfg.define("HAVE_CORETEXT", "1");
        }

        if target.contains("windows") {
            cfg.define("HAVE_DIRECTWRITE", "1");
        }

        if target.contains("windows-gnu") {
            cfg.flag("-Wa,-mbig-obj");
        }

        if let Some(wasi) = &wasm {
            configure_wasm(&mut cfg, wasi, true);
        }
        cfg.compile("harfbuzz");

        let mut sheenbidi = cc::Build::new();
        sheenbidi
            .files(all_files_with_extension(
                "../submodules/SheenBidi/Source",
                "c",
            ))
            .include("../submodules/SheenBidi/Headers")
            .warnings(false);
        if let Some(wasi) = &wasm {
            configure_wasm(&mut sheenbidi, wasi, false);
        }
        sheenbidi.compile("sheenbidi");
    }

    let mut cfg = cc::Build::new();
    cfg.cpp(true)
        .include(rive_cpp_path.join("include"))
        .files(all_files_with_extension(rive_cpp_path.join("src"), "cpp"))
        .flag(cpp_std)
        .define("_RIVE_INTERNAL_", None)
        .warnings(false);

    if cfg!(feature = "text") {
        cfg.include("../submodules/harfbuzz/src")
            .include("../submodules/SheenBidi/Headers")
            .flag_if_supported("-Wno-deprecated-declarations")
            .define("WITH_RIVE_TEXT", None);
    }
    if cfg!(feature = "layout") {
        cfg.include("../submodules/yoga")
            .flag_if_supported("-Wno-deprecated-declarations")
            .define("WITH_RIVE_LAYOUT", None)
            .define("YOGA_EXPORT=", None);
    }

    if let Some(wasi) = &wasm {
        configure_wasm(&mut cfg, wasi, true);
    }
    cfg.compile("rive");

    if let Some(platform_define) = metal_platform_define {
        build_metal_renderer(&rive_cpp_path, platform_define);
    }

    if let Some(wasi) = &wasm {
        emit_wasm_link_flags(wasi);
    }
}
