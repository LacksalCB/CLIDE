use std::process::Command;
use std::env;

pub fn setup_dir(dir: String, dest: String) {
    let home = env::var("HOME").expect("HOME not set"); 
    let install_dir = format!("{home}/.local/share/maker/templates/dirs/");

    let script = format!("{install_dir}{dir}.sh");
    
    println!("Running create script: \'{script}\'");

    let output = Command::new("sh")
        .arg(&script)
        .arg(&dest)
        .output()
        .expect("Failed to execute process");

    println!("{}", String::from_utf8_lossy(&output.stdout));
    eprintln!("{}", String::from_utf8_lossy(&output.stderr));
}
