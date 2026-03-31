#include "../include/cmd_parser.h"
#include "../include/makefile_gen.h"

#include <stdio.h>

// Minimal testing command
// clide init . -l c -m exec -d basic 

/**
 COMMANDS:
  init [DIR]


*/

/**
 FLAGS:
 	
  -m Setup makefile manually
*/

/**
OBJECTIVES:
1. Directory Setup
2. Construct templates (dir setup, makefile, base files)
3. Github setup 
*/

///TODO: 

int main(int argc, char** argv){
	int cmd = -1;
	if (argc > 1) {
		cmd = parse_commands(argc, argv);
		return 0;
	}

	query_makefile();

    return 0;
}
