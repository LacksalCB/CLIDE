mod cmd_parser;
mod dir_setup;
mod makefile_gen;
mod paths;

use std::env;
use std::process::exit;


pub fn run() {
    let args: Vec<String> = env::args().collect();

    // Make more thorough
    if args.len() < 2 {
        println!("Error: missing args");
        exit(1);
    }

    cmd_parser::parse_commands(args);
}
