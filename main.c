#include "main.h"

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
