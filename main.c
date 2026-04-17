#include "main.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL, *args[64]; /* getline buffer */
	size_t len = 0; /* buffer size */
	ssize_t read_chars;
	unsigned int line_count = 0; /* command count */
	int interactive = isatty(STDIN_FILENO); /* check interactive mode */
	int status = 0; /* store last command status */

	(void)argc; /* unused parameter but argv needs a friend */

	while (1)
	{
		if (interactive)
			print_prompt(); /* print prompt only in interactive mode */

		read_chars = getline(&line, &len, stdin); /* read input line */
		if (read_chars == -1)
		{
			free(line);
			exit(status); /* exit with last command status */
		}

		line_count++; /* count every input line */
		clean_input(line); /* remove trailing newline */

		if (parse_input(line, args) == 0)
			continue; /* skip empty lines */

		/* built-in: exit */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line); /* free allocated memory */
			exit(0); /* exit shell */
		}

		status = execute_command(args, argv[0], line_count); /* execute command */
	}
}
