#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Tells the compiler that environ exists somewhere but we are using it here */
/* environ is the environment array that we pass to execve */
extern char **environ;

void print_prompt(void);
void remove_newline(char *line);
int execute_command(char *command. char *shell_name, unsigned int line_count);
void handle_eof(char *line, int interactive);

#endif
