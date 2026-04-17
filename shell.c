#include "main.h"

/**
 * execute_command - executes a command with fork and execve
 * @argv: array of command and arguments
 * @shell_name: name of the shell program
 * @line_count: current command line number
 *
 * Return: child exit status, 127 if command is not found, 1 on failure
 */
int execute_command(char **argv, char *shell_name, unsigned int line_count)
{
	pid_t pid;
	char *comm_path;
	int status = 0;

	if (!argv[0])
		return (0);

	/**
	 * to not call fork if command doesnt exist, have to place
	 * command checker here and return 127 so nothing gets forked
	 */
	comm_path = find_command(argv[0]);
	if (comm_path == NULL)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
			shell_name, line_count, argv[0]);
		return (127);
	}

	pid = fork(); /* create child process */
	if (pid == -1)
	{
		perror("fork"); /* print error if fork fails */
		free(comm_path);
		return (1);
	}

	if (pid == 0)
	{
		execve(comm_path, argv, environ);
		free(comm_path);
		fprintf(stderr, "%s: %u: %s: not found\n",
			shell_name, line_count, argv[0]);
		exit(127);
	}

	waitpid(pid, &status, 0); /* status stores exit code if child exits normally */
	free(comm_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); /* extract child's exit code */

	return (1); /* return error if child did not exit normally */
}
