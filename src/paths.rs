use std::sync::LazyLock;
use std::path::PathBuf;

use platform_dirs::AppDirs;

pub static PREFIX: LazyLock<PathBuf> = LazyLock::new(||  {
    println!("Detected OS: {}", std::env::consts::OS);
    let prefix = AppDirs::new(Some("clide"), true).unwrap().data_dir;

    println!("Detected OS config directory: {}", prefix.display());
    return prefix;
});

