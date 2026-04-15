use std::process::Command;
use std::env;
use std::path::PathBuf;

pub fn setup_dir(dir: &str, dest: &str) {
    let home = env::var("HOME").expect("HOME not set");
    let script = PathBuf::from(&home)
        .join(".local/share/clide/templates/dirs")
        .join(&dir)
        .with_extension(".sh");

    println!("Running create script: \'{}\'", script.display());
    
    println!("{dest}");
    let output = Command::new("sh")
        .arg(&script)
        .arg(&dest)
        .output()
        .expect("Failed to execute process");

    println!("{}", String::from_utf8_lossy(&output.stdout));
    eprintln!("{}", String::from_utf8_lossy(&output.stderr));
}
