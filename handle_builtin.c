#include "shell.h"

/**
 * handle_builtin - Handle the built-in commands
 * @args: The arguments array
 *
 * Return: 1 if the command is a built-in, 0 otherwise
 */
int handle_builtin(char **args)
{
	if (args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		shell_exit();
		return (1);
	}

	if (strcmp(args[0], "env") == 0)
	{
		handle_env();
		return (1);
	}

	return (0);
}
