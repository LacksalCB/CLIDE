use std::sync::LazyLock;
use std::path::PathBuf;

// %USERPROFILE% -> use dir on windows

pub static PREFIX: LazyLock<PathBuf> = LazyLock::new(|| {
    let home_path = home::home_dir().expect("Could not find home directory"); 

    #[cfg(target_os="linux")]
    let path = ".local/share/clide";

    #[cfg(target_os="windows")]
    let path = "%appdata\\clide"; // Fix for windows one day

    #[cfg(target_os="macos")]
    let path = "Library/Application Support/clide";

    #[cfg(not(any(target_os="linux", target_os="windows", target_os="macos")))]
    let path = ".clide";
   
    return home_path.join(&path);
});

