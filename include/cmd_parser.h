#ifndef CMD_PARSER_H
#define CMD_PARSER_H

int flag_lang(char* argv);
int flag_make(char* argv);
int flag_dirs(char* argv);

int cmd_help(int argc, char** argv);
int cmd_init(int argc, char** argv);
int cmd_set_default(int argc, char** argv);

int parse_commands(int argc, char** argv);

typedef struct {
	const char* name;
	int (*cmd_handler) (int argc, char** argv);
	

} command_t;

typedef struct OPT_STRUCT {
    char* lang;
    char* format;
    char* dirs;
} opt_t;

#endif /* CMD_PARSER_H */
