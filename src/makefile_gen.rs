use std::fs;
use std::fs::File;
use std::io::prelude::*;
use std::env;
use std::path::PathBuf;


pub fn load_makefile(path: &PathBuf, dest: &str) -> std::io::Result<()> {
    let home = env::var("HOME").expect("HOME not set");
    let makefile_dir = PathBuf::from(&home)
        .join(".local/share/clide/templates")
        .join(&path)
        .join("Makefile");
    println!("Copying makefile: \'{}\'", makefile_dir.display());

    let makefile_text = fs::read_to_string(&makefile_dir)?;
    
    let mut makefile = File::create(PathBuf::from(dest).join("Makefile"))?;
    makefile.write_all(makefile_text.as_bytes())?;
    Ok(())
}
