use std::fs;
use std::fs::File;
use std::path::PathBuf;

fn load_dirs(config: &PathBuf) -> Vec<String> {
    let dirs = fs::read_to_string(&config).expect("Could not read the directory setup file.");

    let layout:Vec<String> = dirs
        .trim()
        .split(':')
        .map(|s| s.to_string())
        .collect();
    
    layout 
} 

fn create_layout(layout: Vec<String>, dest: &str) -> std::io::Result<()> {
    fs::create_dir_all(dest)?;
    
    for file in layout {
        println!("Creating: {file}");
        let path = PathBuf::from(dest).join(file.clone());
        if file.find('.').is_some() {
            let _ = File::create(PathBuf::from(path.clone())); 
        }
        fs::create_dir_all(path)?; 
    }
    Ok(())
}

pub fn setup_dir(config: &PathBuf, dest: &str) -> std::io::Result<()> {
    println!("Copying dir setup: \'{}\'", config.display());
        
    let layout = load_dirs(config);
   
    create_layout(layout, dest)
}
