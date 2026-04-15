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
	char *comm_path;

	if (argv[0] == NULL)
		return (-1); /* do nothing if command is empty */

	/**
	 * to not call fork if command doesnt exists, have to place
	 * command checker here and return -1 so nothing gets forked
	 */
	comm_path = find_command(argv[0]);
	if (comm_path == NULL)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
				shell_name, line_count, argv[0]);
		return (-1);
	}

	pid = fork(); /* create child process */
	if (pid == -1)
	{
		perror("fork"); /* print error if fork fails */
		free(comm_path);
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(comm_path, argv, environ) == -1) /* accepts ls and /bin/ls */
		{
			perror(shell_name); /* execve failure isnt not found */
			exit(127);
		}
	}
	waitpid(pid, NULL, 0);
	free(comm_path); /* always free your slaves */
	return (0);
}
