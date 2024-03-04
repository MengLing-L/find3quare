extern crate dunce;
use std::{env, path::PathBuf};
use std::process::Command;
fn main() {
	let root: PathBuf = PathBuf::from(env::var_os("CARGO_MANIFEST_DIR").unwrap());
    let library_dir = dunce::canonicalize(root.join("src/lib")).unwrap();
    // 构造一个要运行的 shell 命令，例如运行一个脚本
    let output = Command::new("sh")
        .current_dir(library_dir.clone()) // 设置命令的当前工作目录
        .arg("build.sh") // 脚本的路径 // 可以将输出目录作为参数传递给脚本
        .output() // 运行命令并获取输出
        .expect("Failed to execute command");

    // 打印命令的输出，以便调试
    println!("Status: {}", output.status);
    println!("stdout: {}", String::from_utf8_lossy(&output.stdout));
    println!("stderr: {}", String::from_utf8_lossy(&output.stderr));

    // 如果命令没有成功执行，可以选择退出构建
    if !output.status.success() {
        panic!("Command executed with failing error code");
    }
    println!("cargo:rustc-link-search=native={}", env::join_paths(&[library_dir]).unwrap().to_str().unwrap());
    println!("cargo:rustc-link-lib=static=rust_three_square");
}
