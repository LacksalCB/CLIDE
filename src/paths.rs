use std::sync::LazyLock;
use std::path::PathBuf;

use platform_dirs::AppDirs;

pub static PREFIX: LazyLock<PathBuf> = LazyLock::new(||  {
    let path = 
    if cfg!(target_os = "macos") {
        let home = std::env::var("HOME").expect("Home not set");
        PathBuf::from(home)
            .join("Library")
            .join("Application Support")
            .join("clide")
    } else if cfg!(target_os = "windows") {
        let roaming = std::env::var("APPDATA").expect("APPDATA not set");
        PathBuf::from(roaming).join("clide")
    } else {    
        AppDirs::new(Some("clide"), true).unwrap().data_dir
    };
    path
});

