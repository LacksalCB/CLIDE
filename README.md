# CLIDE-gen
CLIDE-gen (CLI-Development Environment Generator): Suite of Tools written in Rust to set up/modify command line development environments:

# Component Projects: (Very Deprecated)

1. Maker: https://github.com/LacksalCB/maker
2. Snippets: https://github.com/LacksalCB/Snippets

# Usage

`clide [CMD] [OPTION]... [TARGET DIRECTORY]`
Setup Command-LIne Development Environment in DIR.

  -l,  --lang
         specify the language of the target DE

  -f,  --format
         specify the target output file format

  -d,  --dirs
         specify the directory layout of the target DE

  To run default configuration, run with no OPTIONS like: `clide init .` 

# Examples
`clide help` to display help page

`clide .` to run default command (in templates/defaults.txt)

