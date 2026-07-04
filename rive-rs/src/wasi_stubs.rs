use core::ptr;

const WASI_ESUCCESS: i32 = 0;
const WASI_EBADF: i32 = 8;

unsafe fn write_u32(addr: i32, value: u32) {
    unsafe { ptr::write_unaligned(addr as usize as *mut u32, value) }
}

unsafe fn write_u64(addr: i32, value: u64) {
    unsafe { ptr::write_unaligned(addr as usize as *mut u64, value) }
}

unsafe fn read_u32(addr: i32) -> u32 {
    unsafe { ptr::read_unaligned(addr as usize as *const u32) }
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_proc_exit(_code: i32) {
    core::arch::wasm32::unreachable()
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_fd_close(_fd: i32) -> i32 {
    WASI_ESUCCESS
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_fd_fdstat_get(_fd: i32, _stat: i32) -> i32 {
    WASI_EBADF
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_fd_prestat_get(_fd: i32, _buf: i32) -> i32 {
    WASI_EBADF
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_fd_prestat_dir_name(
    _fd: i32,
    _path: i32,
    _len: i32,
) -> i32 {
    WASI_EBADF
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_fd_seek(
    _fd: i32,
    _offset: i64,
    _whence: i32,
    newoffset: i32,
) -> i32 {
    unsafe { write_u64(newoffset, 0) }
    WASI_ESUCCESS
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_fd_write(
    _fd: i32,
    iovs: i32,
    iovs_len: i32,
    nwritten: i32,
) -> i32 {
    let mut total: u32 = 0;
    unsafe {
        for index in 0..iovs_len {
            total = total.wrapping_add(read_u32(iovs + index * 8 + 4));
        }
        write_u32(nwritten, total);
    }
    WASI_ESUCCESS
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_environ_get(_environ: i32, _buf: i32) -> i32 {
    WASI_ESUCCESS
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_environ_sizes_get(
    count: i32,
    buf_size: i32,
) -> i32 {
    unsafe {
        write_u32(count, 0);
        write_u32(buf_size, 0);
    }
    WASI_ESUCCESS
}

#[unsafe(no_mangle)]
pub extern "C" fn __imported_wasi_snapshot_preview1_clock_time_get(
    _id: i32,
    _precision: i64,
    time: i32,
) -> i32 {
    unsafe { write_u64(time, 0) }
    WASI_ESUCCESS
}
