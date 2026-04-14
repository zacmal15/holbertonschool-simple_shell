#include "main.h"

/**
 * print_prompt - prints the shell prompt
 *
 * Return: nothing
 */
void print_prompt(void)
{
	printf("($) "); /* display shell prompt */
	fflush(stdout); /* force prompt to show immediately */
}

/**
 * clean_input - removes newline and surrounding spaces from input
 * @line: pointer to input string
 *
 * Return: pointer to cleaned command
 */
char *clean_input(char *line)
{
	char *start;
	int end;

	if (line == NULL)
		return (NULL);

	line[strcspn(line, "\n")] = '\0'; /* remove trailing newline */
	start = line; /* start at beginning of string */

	while (*start == ' ' || *start == '\t')
		start++; /* skip leading spaces and tabs */

	end = strlen(start) - 1; /* get index of last character */

	while (end >= 0 && (start[end] == ' ' || start[end] == '\t'))
	{
		start[end] = '\0'; /* remove trailing spaces and tabs */
		end--;
	}

	return (start);
}

/**
 * handle_eof - handles end of file condition
 * @line: pointer to input buffer
 * @interactive: checks if shell is in interactive mode
 *
 * Return: nothing
 */
void handle_eof(char *line, int interactive)
{
	if (interactive)
		printf("\n"); /* print newline when Ctrl+D is pressed */

	free(line); /* free getline buffer */
	exit(0); /* exit shell successfully */
}

/**
 * execute_command - executes a command using fork and execve
 * @command: command entered by the user
 * @shell_name: name of the shell program
 * @line_count: current command line number
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *command, char *shell_name, unsigned int line_count)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = command; /* first argument is the command itself */
	argv[1] = NULL; /* argument list must end with NULL */

	if (access(command, X_OK) == -1)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
			shell_name, line_count, command); /* print error message */
		return (-1);
	}

	pid = fork(); /* create child process */

	if (pid == -1)
	{
		perror("fork"); /* print error if fork fails */
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(command, argv, environ) == -1)
		{
			perror(shell_name); /* print error if execve fails */
			exit(EXIT_FAILURE); /* exit child process */
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("wait"); /* print error if wait fails */
			return (-1);
		}
	}

	return (0);
}

/**
 * main - entry point for the simple shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char *line;
	char *command;
	size_t len;
	ssize_t read_chars;
	unsigned int line_count;
	int interactive;

	(void)ac; /* avoid unused parameter warning */
	line = NULL; /* initialize getline buffer */
	len = 0; /* initialize getline size */
	line_count = 0; /* initialize command counter */
	interactive = isatty(STDIN_FILENO); /* check interactive mode */

	while (1)
	{
		if (interactive)
			print_prompt(); /* print prompt only in terminal mode */

		read_chars = getline(&line, &len, stdin); /* read user input */

		if (read_chars == -1)
			handle_eof(line, interactive);

		line_count++; /* increase command counter */
		command = clean_input(line); /* clean spaces and newline */

		if (command[0] == '\0')
			continue; /* skip empty or spaces-only lines */

		execute_command(command, av[0], line_count); /* run command */
	}
}
