use std::fs;
use std::fs::File;
use std::io::prelude::*;
use std::path::PathBuf;

pub fn load_makefile(path: &PathBuf, dest: &str) -> std::io::Result<()> {
    println!("Copying makefile: \'{}\'", path.display());

    let makefile_text = fs::read_to_string(&path)?;
    
    let mut makefile = File::create(PathBuf::from(dest).join("Makefile"))?;
    makefile.write_all(makefile_text.as_bytes())?;
    Ok(())
}
