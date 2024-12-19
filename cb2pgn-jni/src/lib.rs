use jni::JNIEnv;
use jni::objects::{JClass, JString};
use jni::sys::jstring;
use std::path::Path;

#[no_mangle]
pub extern "system" fn Java_org_chess_cb_Cb2Pgn_extractCbv(
    env: JNIEnv,
    _class: JClass,
    input_path: JString,
    output_dir: JString,
) -> jstring {
    let input_path: String = env
        .get_string(&input_path)
        .expect("Couldn't get input path string")
        .into();
    
    let output_dir: String = env
        .get_string(&output_dir)
        .expect("Couldn't get output directory string")
        .into();

    // Read the input file
    let input_data = std::fs::read(&input_path).expect("Failed to read input file");
    
    // Create output directory if it doesn't exist
    std::fs::create_dir_all(&output_dir).expect("Failed to create output directory");

    // Parse and extract files
    match uncbv::extract_files(&input_data, &output_dir) {
        Ok(_) => {
            let result = format!("Successfully extracted files to {}", output_dir);
            let output = env.new_string(&result)
                .expect("Couldn't create Java string");
            output.into_raw()
        },
        Err(e) => {
            let error_msg = format!("Failed to extract files: {}", e);
            let output = env.new_string(&error_msg)
                .expect("Couldn't create Java string");
            output.into_raw()
        }
    }
} 