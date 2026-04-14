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
	start = line; /* point to beginning of string */

	while (*start == ' ' || *start == '\t')
		start++; /* skip leading spaces and tabs */

	end = strlen(start) - 1; /* find last character index */

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
		printf("\n"); /* print newline on Ctrl+D */

	free(line); /* free input buffer */
	exit(0); /* exit shell */
}

/**
 * parse_input - splits input line into command and arguments
 * @line: cleaned input line
 * @argv: array to store tokens
 *
 * Return: number of tokens
 */
int parse_input(char *line, char **argv)
{
	int i;
	char *token;

	i = 0;
	token = strtok(line, " \t"); /* split using space and tab */

	while (token != NULL)
	{
		argv[i] = token; /* store token in argv array */
		i++;
		token = strtok(NULL, " \t"); /* get next token */
	}

	argv[i] = NULL; /* terminate argv array */
	return (i);
}

/**
 * execute_command - executes a command using fork and execve
 * @argv: array of command and arguments
 * @shell_name: name of the shell program
 * @line_count: current command line number
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **argv, char *shell_name, unsigned int line_count)
{
	pid_t pid;
	int status;

	if (access(argv[0], X_OK) == -1)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
			shell_name, line_count, argv[0]); /* print error message */
		return (-1);
	}

	pid = fork(); /* create child process */

	if (pid == -1)
	{
		perror("fork"); /* print fork error */
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(shell_name); /* print execve error */
			exit(EXIT_FAILURE); /* exit child if execve fails */
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("wait"); /* print wait error */
			return (-1);
		}
	}

	return (0);
}
