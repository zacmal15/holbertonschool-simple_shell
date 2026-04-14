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
 * handle_eof - handles end of file condition
 * @line: pointer to getline buffer
 * @interactive: checks if shell is in interactive mode
 *
 * Return: nothing
 */
void handle_eof(char *line, int interactive)
{
	if (interactive)
		printf("\n"); /* print newline on Ctrl + D */

	free(line); /* free getline buffer before exiting */
	exit(0); /* exit shell successfully */
}

/**
 * clean_input - removes newline from the input string
 * @line: input string read by getline
 *
 * Return: nothing
 */
void clean_input(char *line)
{
	if (line != NULL)
		line[strcspn(line, "\n")] = '\0'; /* replace newline with null byte */
}
