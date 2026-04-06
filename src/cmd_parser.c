#include "../include/cmd_parser.h"
#include "../include/makefile_gen.h"
#include "../include/dir_setup.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdarg.h>

#define CMD_LEN (sizeof(commands)/sizeof(commands[0]))
command_t commands[] = {
    {"help", cmd_help},
	{"init", cmd_init},
    {"set-default", cmd_set_default},
};

static struct option flag_options[] = {
	{"lang", required_argument, 0, 'l'},
	{"format", required_argument, 0, 'f'},
	{"dirs", required_argument, 0, 'd'},
};

int cmd_help(int argc, char** argv) {
    puts("Usage: rm [CMD] [OPTION]... [DIR]");
    puts("Setup Command-LIne Development Environment in DIR.");

    printf("  \033[1;94m-l,  --lang\033[0m,\n");
    puts("        specify the language of the target DE");

    printf("  \033[1;94m-f,  --format\033[0m,\n");
    puts("        specify the target output file format");

    printf("  \033[1;94m-d,  --dirs\033[0m,\n");
    puts("        specify the directory layout of the target DE");


    return 0;
}

int cmd_init(int argc, char** argv) {
	if (argc < 3 || argv[2][0] == '-') {
		fprintf(stderr, "Init: missing source directory\nTry \'cenv init --help\' for more information.\n");
		exit(1);
	}	

	char path[256];
   
    opt_t opts;

    int opt = 0;

    while ((opt = getopt_long(argc, argv, "l:f:d:h", flag_options, NULL)) != -1) {
		switch (opt) {
			case 'l':
			    opts.lang = optarg;
				break;
			case 'f':
				opts.format = optarg;
				break;
			case 'd':
				opts.dirs =  optarg;
				break;
			default:
				fprintf(stderr, "Init: invalid option \'%c\'\nTry \'cenv init --help\' for more information.\n", opt);
				exit(1);	
		}
	} 

	if (!opts.lang || !opts.format || !opts.dirs) {
		fprintf(stderr, "Init: must specify language, format, and directory layout\nTry \'cenv init --help\' for more information.\n");
		exit(1);
	}

	setup_dir(opts.dirs);
	snprintf(path, sizeof(path), "templates/makefiles/%s/%s/%s", opts.lang, opts.format, opts.dirs);
	load_template(path);
	
	return 0;
}

int cmd_set_default (int argc, char** argv) {


}

int parse_commands(int argc, char** argv) {
	for (size_t i = 0; i < CMD_LEN; i++) {
		if (strcmp(argv[1], commands[i].name) == 0) {
			return commands[i].cmd_handler(argc, argv);	
		}	
	}	

	return 0;
}

