#include "main.h"

/**
 * get_path - i cant use getpath so ill do it myself
 *
 * Return: the directories
 */

char *get_path(void)
{
	int i = 0;

	/* search environment for PATH, returns where the directories are */
	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5); /* location of dirs after colon */
	}
	return (NULL);
}

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
	if (strchr(comm, '/')) /* direct path case */
	{
		if (access(comm, X_OK) == 0)
		/* if access is successful, return command */
			return (strdup(comm));
		return (NULL);
	}
	path_env = get_path();
	if (!path_env)
		return (NULL);
	copy = strdup(path_env); /* so as to not change environ */
	if (!copy)
		return (NULL);

	dir = strtok(copy, ":"); /* split PATH into directories with colon */
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(comm) + 2);
		/* add 2 for null terminator and the forward slash */
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
