#include "main.h"

/**
 * find_command - checks if command exists in path
 * @comm: command
 *
 * Return: full path if exists, NULL if not
 */

char *find_command(char *comm)
{
	char *path_env, *copy, *full_path, *dir;

	if (comm == NULL)
		return (NULL);

	if (access(comm, X_OK) == 0) /* direct path case */
		/* if access is successful, return command */
		return (comm);

	path_env = getenv("PATH"); /* gets PATH from the environment */
	if (!path_env)
		return (NULL);
	copy = strdup(path_env); /* so as to not change environ */
	if (!copy)
		return (NULL);

	dir = strtok(copy, ":"); /* split PATH into directories with colon */
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(comm) + 2);
		/* add 2 for null terminator */
		if (!full_path)
		{
			free(copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, comm);
		if (access(full_path, X_OK) == 0) /* check access */
		{
			free(copy);
			return (full_path);
		}
		/* cleanup */
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(copy);
	return (NULL);
}
