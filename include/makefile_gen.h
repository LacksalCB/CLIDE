#ifndef MAKEFILE_GEN_H
#define MAKEFILE_GEN_H

// Makefile struct
// add enums and stuff for presets
typedef struct MAKEFILE_STRUCT {
	char* contents;
	char* language;
	char** file_structure;
	int file_count;
	char* output_format;
	char* flags;
	char* all_targets;
	char* install;
	char* clean_targets;
	char* misc;
} makefile_t;

// Generic Template Struct
typedef struct TEMPLATES_STRUCT {
	int template_index;
	int template_count;
	char** template_names;
}maker_template_t;

// Dynamic Template Functions
extern const char* supported_languages;

void prompt_language(makefile_t* makefile);
void prompt_dir_structure(makefile_t* makefile);
void prompt_output_format(makefile_t* makefile);
void prompt_flags(makefile_t* makefile);
void prompt_all_targets(makefile_t* makefile);
void prompt_install(makefile_t* makefile);
void prompt_clean_targets(makefile_t* makefile);
void prompt_misc(makefile_t* makefile);

void set_language(makefile_t* makefile);
void set_dir_structure(makefile_t* makefile);
void set_output_format(makefile_t* makefile);
void set_flags(makefile_t* makefile);
void set_all_targets(makefile_t* makefile);
void set_install(makefile_t* makefile);
void set_clean_targets(makefile_t* makefile);
void set_misc(makefile_t* makefile);

void dealloc_makefile(makefile_t* makefile);

void generate_template();

// Static Template Functions

void load_template(int template_num);
void select_template();

extern maker_template_t templates;

void init_templates(maker_template_t* template);
void get_template();
void add_template(maker_template_t* template, char* str);
void remove_template();
void destroy_templates(maker_template_t* template);

#endif
