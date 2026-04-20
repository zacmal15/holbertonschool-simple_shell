#include "main.h"

/**
 * print_prompt - prints the shell prompt
 *
 * Return: nothing
 */
void print_prompt(void)
{
	printf("(good_boy$) "); /* display shell prompt */
	fflush(stdout); /* force prompt to appear immediately */
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
