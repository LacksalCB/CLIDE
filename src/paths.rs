use phf::phf_map;

static PATHS: phf::Map<&'static str, &str> = phf_map! {
    "linux" => "./local/share/clide",
    "win" => "%appdata%/clide",
    "mac" => "Library/Application Support/clide",
};


pub fn load_path(file: &str) -> &str {
    let os = std::env::consts::OS;    

    if let Some(path) = PATHS.get(os) { 
        println!("path: {}", path);

    } else {
        println!("Invalid OS");
    }

    return "h";
}
