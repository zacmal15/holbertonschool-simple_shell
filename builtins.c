#include "main.h"

/**
 * print_env - prints the current environment
 *
 * Return: nothing
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]); /* print one environment variable */
		i++;
	}
}

/**
 * shell_exit - exits the shell
 * @line: getline buffer to free
 * @status: exit status to return
 *
 * Return: nothing
 */
void shell_exit(char *line, int status)
{
	free(line); /* free allocated buffer */
	exit(status); /* exit shell with given status */
}
