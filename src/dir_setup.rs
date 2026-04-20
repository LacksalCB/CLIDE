use std::process::Command;
use std::path::PathBuf;

pub fn setup_dir(script: &PathBuf, dest: &str) {
    println!("Running dir setup script: \'{}\'", script.display());
    let output = Command::new("sh")
        .arg(&script)
        .arg(&dest)
        .output()
        .expect("Failed to execute process");

    println!("{}", String::from_utf8_lossy(&output.stdout));
    eprintln!("{}", String::from_utf8_lossy(&output.stderr));
}
