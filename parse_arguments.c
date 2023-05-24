#include "shell.h"

/**
 * parse_arguments - Parse the command into arguments
 * @command: The command to parse
 *
 * Return: An array of arguments
 */
char **parse_arguments(char *command)
{
	char **args = malloc(sizeof(char *));
	char *token;
	int i = 0;

	if (args == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(command, " \t\n");
	while (token != NULL)
	{
		args[i++] = token;
		args = realloc(args, (i + 1) * sizeof(char *));

		if (args == NULL)
		{
			perror("realloc");
			return (NULL);
		}

		token = strtok(NULL, " \t\n");
	}

	args[i] = NULL;
	return (args);
}
