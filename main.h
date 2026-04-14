#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

void print_prompt(void);
char *clean_input(char *line);
void handle_eof(char *line, int interactive);
int execute_command(char *command, char *shell_name, unsigned int line_count);

#endif
