use std::ffi::CStr;
use std::os::raw::c_char;

#[no_mangle]
pub extern "system" fn Java_com_cb2pgn_CBVExtractor_extract(
    _env: *mut std::ffi::c_void,
    _class: *mut std::ffi::c_void,
    input_path: *const c_char,
    output_dir: *const c_char,
) -> i32 {
    let input_path = unsafe { CStr::from_ptr(input_path) }.to_str().unwrap();
    let output_dir = unsafe { CStr::from_ptr(output_dir) }.to_str().unwrap();

    match uncbv::archive::decrypt_archive(input_path, Some(output_dir.to_string()), true) {
        true => 0,
        false => -1,
    }
} 