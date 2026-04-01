#include "../include/makefile_gen.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

// Dynamic Makefile Generation 
const char* supported_languages = "C/C++";

void prompt_language(makefile_t* makefile) {
	char* language_prompt = NULL;
	size_t line_len = 0;
	ssize_t buf;

	printf("\nWhat language is this makefile for? (%s)\n", supported_languages);

	for (;;) {
		buf = getline(&language_prompt, &line_len, stdin);
		if (buf == -1) {
			fprintf(stderr, "Error reading input\n");
			return;
		}

		if (buf > 0 && language_prompt[buf-1] == '\n') {
			language_prompt[buf-1] = '\0';
		}

		if (strstr(supported_languages, language_prompt)) {
			break;
		}

		puts("Please enter a language from the supported language list.");
	}
	makefile->language = language_prompt;
}

void prompt_file_structure(makefile_t* makefile) {
	puts("\nWhat is your intended file structure? (simple single dir project, or multiple dirs like src, include etc)\n1) Simple\n2) Custom\n");

	int fs_option = 0;
	char** fs_prompt = NULL;
	int file_count = 0;

	
	char* file;
	for (;;) {
		int buf = scanf("%d", &fs_option);

		if (buf == EOF) {
			fprintf(stderr, "Error reading input\n");
			return;
		}

		if (fs_option == 1) {	
			break;
		}

		if (fs_option == 2) {
			puts("\nEnter the desired number of files:");
			scanf("%d", &file_count);

			puts("\nEnter desired file names:");			
			for (int i = 0; i < file_count+1; i++) {
				size_t line_len = 0;
				ssize_t buf = getline(&file, &line_len, stdin);
				if (buf == -1) {
					fprintf(stderr, "Error reading input\n");
					return;
				}

				if (buf > 0 && file[buf-1] == '\n') {
					file[buf-1] = '\0';
				}

				fs_prompt = realloc(fs_prompt, sizeof(char*) * (i + 1));
				fs_prompt[i] = malloc(sizeof(char) * (strlen(file) + 1));
				strcpy(fs_prompt[i], file);
			}
			break;
		}
	}

	free(file);
	makefile->file_structure = fs_prompt;	
	makefile->file_count = file_count;
}

void set_language(makefile_t* makefile) {	
	if (strcmp("C", makefile->language)) {	
		strncpy(makefile->contents, "CC = GCC\n\n", 11);
	}	
	if (strcmp("C++", makefile->language)) {
		strncpy(makefile->contents, "CC = GPP\n\n", 11);
	}
}

char* str_toupper(char* str) {
	char* s = malloc(sizeof(char) * (strlen(str) + 1));

	for (int i = 0; i < (int)strlen(str); i++) {
		s[i] = toupper(str[i]);	
	}

	s[strlen(str)] = 0;
	puts(s);
	return s;
}

void set_file_structure(makefile_t* makefile) {
	const char* file_decl_skeleton = "_DIR = ";	

	// Explore why 0 index prints nothing to contents.  
	for (int i = 1; i <= makefile->file_count; i++) {
		char* makefile_file_name = str_toupper(makefile->file_structure[i]);
		char file_decl[128];
		sprintf(file_decl, "%s%s%s\n", makefile_file_name, file_decl_skeleton, makefile->file_structure[i]);
		strcat(makefile->contents, file_decl);
		free(makefile_file_name);
	}
}

void set_output_format(makefile_t* makefile) {

}

void dealloc_makefile(makefile_t* makefile) {
	free(makefile->contents);
	free(makefile->language);	
	for (int i = 0; i <= makefile->file_count; i++) {
		free(makefile->file_structure[i]);	
	}
	free(makefile->file_structure);
/*
	free(makefile->output_format);
	free(makefile->flags);
	free(makefile->all_targets);
	free(makefile->install);
	free(makefile->clean_targets);
	free(makefile->misc);
*/
	free(makefile);
}

void generate_template() {
	makefile_t* makefile = malloc(sizeof(struct MAKEFILE_STRUCT) * 1);
	makefile->contents = malloc(sizeof(char) * 4096);

	prompt_language(makefile);
 	set_language(makefile);

	prompt_file_structure(makefile);
	set_file_structure(makefile);

	
	puts(makefile->contents);
	
	dealloc_makefile(makefile);
}

// Static Makefile Generation

void write_makefile(char* makefile, long fsize) {
	FILE* fptr;
	if (access("Makefile", F_OK) == 0 ) {
		puts("Overwite existing Makefile? (y/n)");
		char overwrite_query;
		scanf(" %c", &overwrite_query);

		if (overwrite_query == 'y') {
			puts("Creating \'Makefile\'...");
			fptr = fopen("Makefile", "w");
			fwrite(makefile, sizeof(char), fsize, fptr);
			fclose(fptr);	
		} else {
			puts(makefile);	
		}
		return;
	}

	puts("Creating \'Makefile\'...");
	fptr = fopen("Makefile", "w");
	fwrite(makefile, sizeof(char), fsize, fptr);
	fclose(fptr);
}

void load_template(const char* file) {
	FILE* fptr;
	char filename[512];	
	sprintf(
		filename, 
		"%s/.local/share/maker/%s/Makefile", 
		getenv("HOME"), 
		file
	);
	fptr = fopen(filename, "r");

	if (!fptr) {
		fprintf(stderr, "\'%s\' does not exist.\n  Loading from local source files instead.\n", filename);
	    memset(filename, 0, sizeof(filename));
	    sprintf(filename, "%s/Makefile", file);
	    fptr = fopen(filename, "r");
    }

	fseek(fptr, 0, SEEK_END);
	long fsize = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	char* buff = malloc(fsize + 1);
	fread(buff, fsize, 1, fptr);
	fclose(fptr);
	buff[fsize] = 0; // Null Char termination

	write_makefile(buff, fsize);

	free(buff);
}

void select_template() {
	puts("Please select a template:");

	for (int i = 0; i < templates.template_count; i++) {
		printf("%d) %s\n", i+1, templates.template_names[i]);	
	}

	/*
	unsigned short template_style;
	scanf(" %hu", &template_style);
	switch (template_style) {
		case 1: 
			load_template(0);
			break;
		case 2:
			load_template(1);
			break;
		case 3:
			load_template(2);
			break;
		default:
			puts("Invalid option.");
	*/
	
}

// Template Loader


maker_template_t templates;

void init_templates(maker_template_t* templates) {
	templates->template_index = 0;
	templates->template_count = 0;	
	templates->template_names = NULL;
	add_template(templates, "c_exec.txt");
	add_template(templates, "c_static_lib.txt");
	add_template(templates, "c_dyn_lib.txt");
}

void get_template() {
	
}

void add_template(maker_template_t* templates, char* str) {
	templates->template_names = realloc(templates->template_names, sizeof(char*) * (templates->template_count+1));
	templates->template_names[templates->template_count] = strdup(str);
	templates->template_count += 1;
}

void remove_template(  ) {
	
}

void destroy_templates(maker_template_t* templates) {
	for (int i = 0; i < templates->template_count; i++) {
		free(templates->template_names[i]);
		templates->template_names[i] = NULL;
	}
	free(templates->template_names);
}

void query_makefile() {
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
}
