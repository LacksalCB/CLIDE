#include "../include/dir_setup.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void setup_dir(char* dirs) {
	char filename[256];		
	sprintf(
		filename, 
		"%s/.local/share/maker/templates/dirs/%s.sh", 
		getenv("HOME"), 
		dirs
	);

	pid_t pid = fork();

	if (pid == 0) {
		execl("/bin/bash", "bash", filename, NULL);

		perror("exec fail");
	} else {
		wait(NULL);
	}

	if (access(filename, F_OK)  != 0) {
		fprintf(stderr, "\'%s\' does not exist.\n  Loading from local source files instead.\n", filename);
	}

	memset(filename, 0, sizeof(filename));
	sprintf(filename, "templates/dirs/%s.sh", dirs);
}
