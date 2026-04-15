use std::fs;
use std::fs::File;
use std::io::prelude::*;
use std::env;

pub fn load_makefile(path: String, dest: String) -> std::io::Result<()> {
    let home = env::var("HOME").expect("HOME not set");
    let makefile_dir = format!("{home}/.local/share/clide/templates/{path}/Makefile");
    println!("Copying makefile: \'{makefile_dir}\'");

    let makefile_text = fs::read_to_string(&makefile_dir).expect("Should not be able to read from host file");
    println!("{makefile_text}");
    

    let mut makefile = File::create(format!("{dest}/Makefile"))?;
    makefile.write_all(&makefile_text.as_bytes())?;
    Ok(())
}
