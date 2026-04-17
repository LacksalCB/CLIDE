use std::sync::LazyLock;
use std::path::PathBuf;

use platform_dirs::AppDirs;

// %USERPROFILE% -> use dir on windows

pub static PREFIX: LazyLock<PathBuf> = LazyLock::new(||  {
    let prefix = AppDirs::new(Some("clide"), true).unwrap().data_dir;

    return prefix;
});

