#include "main.h"

/**
 * parse_input - splits input into command and arguments
 * @line: cleaned input string
 * @argv: array that stores tokens
 *
 * Return: number of tokens found
 */
int parse_input(char *line, char **argv)
{
	int i;
	char *token;

	i = 0;
	token = strtok(line, " \t"); /* get first token using space and tab */

	while (token != NULL)
	{
		argv[i] = token; /* store token in argument array */
		i++;
		token = strtok(NULL, " \t"); /* get next token */
	}

	argv[i] = NULL; /* mark end of argument array */
	return (i);
}
