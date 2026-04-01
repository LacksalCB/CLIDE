#include "../include/cmd_parser.h"
#include "../include/makefile_gen.h"
#include "../include/dir_setup.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#define CMD_LEN (sizeof(commands)/sizeof(commands[0]))
command_t commands[] = {
	{"init", cmd_init},
};

static struct option flag_options[] = {
	{"lang", required_argument, 0, 'l'},
	{"format", required_argument, 0, 'f'},
	{"dirs", required_argument, 0, 'd'},
	{"help", no_argument, 0, 'h'},
};

int cmd_init(int argc, char** argv) {
	if (argc < 3 || argv[2][0] == '-') {
		fprintf(stderr, "Init: missing source directory\nTry \'cenv init --help\' for more information.\n");
		exit(1);
	}	

	char path[256];
	int opt = 0;

	char* lang = NULL;
	char* format = NULL;
	char* dirs = NULL;

	while ((opt = getopt_long(argc, argv, "l:f:d:h", flag_options, NULL)) != -1) {
		switch (opt) {
			case 'l':
				lang = optarg;
				break;
			case 'f':
				format = optarg;
				break;
			case 'd':
				dirs = optarg;
				break;
			default:
				fprintf(stderr, "Init: invalid option \'%c\'\nTry \'cenv init --help\' for more information.\n", opt);
				exit(1);	
		}
	}

	if (!lang || !format || !dirs) {
		fprintf(stderr, "Init: must specify language, format, and directory layout\nTry \'cenv init --help\' for more information.\n");
		exit(1);
	}

	setup_dir(dirs);
	snprintf(path, sizeof(path), "templates/makefiles/%s/%s/%s", lang, format, dirs);
	load_template(path);
	
	return 0;
}

int parse_commands(int argc, char** argv) {
	for (size_t i = 0; i < CMD_LEN; i++) {
		if (strcmp(argv[1], commands[i].name) == 0) {
			return commands->cmd_handler(argc, argv);	
		}	
	}	

	return 0;
}

