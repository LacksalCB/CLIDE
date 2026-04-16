use crate::dir_setup::setup_dir;
use crate::makefile_gen::load_makefile;
use crate::paths::load_path;

use phf::phf_map;
use std::process::exit;
use std::fs;
// TODO: Move to clap, supposedly more modern and robust handling of CLI arguments
use getopts::Options;
use std::path::PathBuf;

#[derive(Debug)]
pub enum CmdError {
    MissingFlag(String),
    ParseError(String),
}

impl std::fmt::Display for CmdError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            CmdError::MissingFlag(flag) => write!(f, "Error, missing flag --{}", flag),
            CmdError::ParseError(msg) => write!(f, "Parse Error:  {}", msg),
        }
    }
}

fn require_opt(matches: &getopts::Matches, flag: &str) -> Result<String, CmdError> {
    matches 
        .opt_str(flag)
        .ok_or_else(|| CmdError::MissingFlag(flag.to_string()))
}

fn load_template(lang: &str, format: &str, dirs: &str, dest: &str) -> Result<i8, CmdError> {
    load_path(&lang);
    let makefile = "makefiles";
    let path = PathBuf::from(&makefile)
        .join(&lang)
        .join(&format)
        .join(&dirs);

    // Same here, setup_dir_default() etc to handle logic elsewhere
    setup_dir(dirs, &dest);
    let _ = load_makefile(&path, dest); // HANDLE 

    Ok(0) 
}

fn cmd_help(_args: Vec<String>) -> Result<i8, CmdError> {
    println!("Usage: clide [CMD] [OPTION]... [ARGS]...");
    println!("Setup Command-LIne Development Environment in DIR.");

    println!("  \x1b[1m-l,  --lang\x1b[0m");
    println!("         specify the language of the target DE\n");

    println!("  \x1b[1m-f,  --format\x1b[0m");
    println!("         specify the target output file format\n");

    println!("  \x1b[1m-d,  --dirs\x1b[0m");
    println!("         specify the directory layout of the target DE\n"); 

    Ok(0)
}

fn cmd_default(dest: &str) -> Result<i8, CmdError> {
    // TODO: Make relative, not hardcoded (and handle install script issue...)
    let default_file = "templates/defaults.txt";

    let default_args = fs::read_to_string(&default_file).expect("Failed to read Defaults file");
    let args:Vec<&str> = default_args.split(':').collect();

    let lang = args[0];
    let format = args[1];
    let dirs = args[2].trim_end();

    let _ = load_template(&lang, &format, &dirs, &dest);

    Ok(0)
}

fn cmd_init(args: Vec<String>) -> Result<i8, CmdError>  {  
    let mut opts = Options::new();  
    // TODO: Add target language speciic build system (like make,cmake,ninja,just for C/C++, or cargo
    // etc for rust
    opts.optopt("l", "lang", "specify the language of the target DE", "LANGUAGE");
    opts.optopt("f", "format", "specify the target output file format", "FORMAT");
    opts.optopt("d", "dirs", "specify the directory layout of the target DE", "DIR_LAYOUT");

    let dest = &args[2];

    if args.len() <= 3 {
        return cmd_default(dest);
    }
    
    let matches = opts
        .parse(&args[2..])
        .map_err(|e| CmdError::ParseError(e.to_string()))?;

    let required: &[&str] = &["l", "f", "d"];
    for flag in required {
        require_opt(&matches, flag)?;
    }

    let lang = require_opt(&matches, "l")?;
    let format = require_opt(&matches, "f")?;
    let dirs = require_opt(&matches, "d")?;
   
    let _ = load_template(&lang, &format, &dirs, dest); 

    Ok(0)
}

fn cmd_set_default(args: Vec<String>) -> Result<i8, CmdError> {
    if args[2].is_empty() {
    
    }
    Ok(0)
}

static COMMANDS: phf::Map<&'static str, fn(Vec<String>) -> Result<i8, CmdError>> = phf_map! {
    "help" => cmd_help as fn(Vec<String>) -> Result<i8, CmdError>,
    "init" => cmd_init as fn(Vec<String>) -> Result<i8, CmdError>,
    "set_default" => cmd_set_default as fn(Vec<String>) -> Result<i8, CmdError>,
};

// Make return option and handle issues
pub fn parse_commands(args: Vec<String>) {
    // TODO: Handle args length issues here and do some input sanitization
    

    if let Some(cmd_helper) = COMMANDS.get(&args[1]) {
        match cmd_helper(args) {
            Ok(_) => {}
            Err(e) => {
                eprintln!("{}", e);
                std::process::exit(1);
            }
        }
    } else {
        // Make better
        println!("Invalid command \'{}\'", args[1]);
        println!("Try \'clide help\' for more information");

        exit(1);
    }   
}


