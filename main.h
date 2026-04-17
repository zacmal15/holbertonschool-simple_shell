#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;
/* called environ somewhere and it stores a list of strings */

void print_prompt(void);
void handle_eof(char *line, int interactive);
void clean_input(char *line);
int parse_input(char *line, char **argv);
int execute_command(char **argv, char *shell_name, unsigned int line_count);
char *find_command(char *comm);
char *get_path(void);
void print_env(void);
void shell_exit(char *line, int status);

#endif
