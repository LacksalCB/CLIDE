use crate::dir_setup::setup_dir;
use crate::makefile_gen::load_makefile;

use phf::phf_map;
use std::process::exit;
extern crate getopts;
use getopts::Options;

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

fn cmd_help(_args: Vec<String>) -> Result<i8, CmdError> {
    println!("Usage: rm [CMD] [OPTION]... [DIR]");
    println!("Setup Command-LIne Development Environment in DIR.");

    println!("  \x1b[1m-l,  --lang\x1b[0m");
    println!("         specify the language of the target DE\n");

    println!("  \x1b[1m-f,  --format\x1b[0m");
    println!("         specify the target output file format\n");

    println!("  \x1b[1m-d,  --dirs\x1b[0m");
    println!("         specify the directory layout of the target DE\n"); 

    Ok(0)
}

fn cmd_init(args: Vec<String>) -> Result<i8, CmdError>  {  
    let mut opts = Options::new();  
    opts.optopt("l", "lang", "specify the language of the target DE", "LANGUAGE");
    opts.optopt("f", "format", "specify the target output file format", "FORMAT");
    opts.optopt("d", "dirs", "specify the directory layout of the target DE", "DIR_LAYOUT");
    
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

    let path = format!("makefiles/{lang}/{format}/{dirs}");
    println!("{}", path);  

    setup_dir(dirs, args[2].clone());
    load_makefile(path, args[2].clone());

    Ok(0)
}

fn cmd_default(args: Vec<String>) -> Result<i8, CmdError> {
    if args[2] == "".to_string() {
        
    }
    Ok(0)
}

fn cmd_set_default(args: Vec<String>) -> Result<i8, CmdError> {
    if args[2] == "".to_string() {
    
    }
    Ok(0)
}

static COMMANDS: phf::Map<&'static str, fn(Vec<String>) -> Result<i8, CmdError>> = phf_map! {
    "help" => cmd_help as fn(Vec<String>) -> Result<i8, CmdError>,
    "init" => cmd_init as fn(Vec<String>) -> Result<i8, CmdError>,
    "default" => cmd_default as fn(Vec<String>) -> Result<i8, CmdError>,
    "set_default" => cmd_set_default as fn(Vec<String>) -> Result<i8, CmdError>,
};

pub fn parse_commands(args: Vec<String>) -> i8 {
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
        println!("Error: invalid command \'{}\'", args[1]);
        exit(1);
    }   

    return 0;
}


