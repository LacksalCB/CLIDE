use phf::phf_map;
use std::path::PathBuf;
use std::env;

static PATHS: phf::Map<&'static str, &str> = phf_map! {
    "linux" => "./local/share/clide",
    "win" => "%appdata%/clide",
    "mac" => "Library/Application Support/clide",
};

// %USERPROFILE%


pub fn load_path(_file: &str) -> &str {
    let os = std::env::consts::OS;    

    let home = if os == "windows" {
        env::var("%USERPROFILE%").unwrap_or_else(|_| "%USERPROFILE%".to_string())
    } else {
        env::var("HOME").expect("HOME not set")
    };

    if let Some(path) = PATHS.get(os) {
        let prefix = PathBuf::from(&home).join(&path);
        println!("path: {}", prefix.display());

    } else {
        println!("Invalid OS");
    }

    return "h";
}
