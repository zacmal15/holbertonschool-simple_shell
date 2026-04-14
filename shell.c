#include "main.h"

/**
 * execute_command - executes a command with fork and execve
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

	if (argv[0] == NULL)
		return (-1); /* do nothing if command is empty */

	if (access(argv[0], X_OK) == -1)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
			shell_name, line_count, argv[0]); /* print error message */
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
		execve(argv[0], argv, environ); /* execute command in child */
		perror(shell_name); /* print error if execve fails */
		exit(EXIT_FAILURE); /* exit child process on failure */
	}

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid"); /* print error if waitpid fails */
		return (-1);
	}

	return (0);
}
