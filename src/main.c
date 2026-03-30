#include "../include/makefile_gen.h"

#include <stdio.h>

/**
OBJECTIVES:
1. Directory Setup
2. Construct templates (dir setup, makefile, base files)
3. Github setup 
*/

///TODO: 

int main(int argc, char** argv){
    puts("Would you like to use a template or generate a custom Makefile?");
	puts("1) Template\n2) Custom");

	unsigned short choice;
	scanf("%hu", &choice);

	while (choice > 2) {
		puts("Please select a valid option.  (1 or 2)");
		scanf("%hu", &choice);
	}

	while (getchar() != '\n');
	init_templates(&templates);
	if (choice == 1) {
		select_template();
	} else if (choice == 2) {
		generate_template();
	}
	destroy_templates(&templates);

    return 0;
}
