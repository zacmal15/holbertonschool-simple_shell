#include "main.h"

/**
 * print_prompt - prints the shell prompt
 *
 * Return: nothing
 */
void print_prompt(void)
{
	printf("($) "); /* display shell prompt */
	fflush(stdout); /* force prompt to appear immediately */
}

/**
 * remove_newline - removes the newline character from input
 * @line: pointer to the input string
 *
 * Return: nothing
 */
void remove_newline(char *line)
{
	if (line != NULL)
		line[strcspn(line, "\n")] = '\0'; /* replace newline with null */
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
	argv[1] = NULL; /* argument array must end with NULL */

	if (access(command, X_OK) == -1)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
			shell_name, line_count, command); /* print error message */
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
		if (execve(command, argv, environ) == -1)
		{
			perror(shell_name); /* print execve error */
			exit(EXIT_FAILURE); /* exit child process on failure */
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
	size_t len;
	ssize_t read_chars;
	unsigned int line_count;
	int interactive;

	(void)ac; /* avoid unused parameter warning */
	line = NULL; /* initialize line pointer */
	len = 0; /* initialize buffer size */
	line_count = 0; /* initialize command counter */
	interactive = isatty(STDIN_FILENO); /* check interactive mode */

	while (1)
	{
		if (interactive)
			print_prompt(); /* print prompt in interactive mode */

		read_chars = getline(&line, &len, stdin); /* read input line */

		if (read_chars == -1)
			handle_eof(line, interactive);

		line_count++; /* count command lines */
		remove_newline(line); /* remove trailing newline */

		if (line[0] == '\0')
			continue; /* skip empty lines */

		execute_command(line, av[0], line_count); /* run command */
	}
}
