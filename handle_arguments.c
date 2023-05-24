#include "shell.h"

/**
 * handle_arguments - Handle the command arguments
 * @command: The command with arguments
 *
 * Return: No return value
 */
void handle_arguments(char *command)
{
	char **args = parse_arguments(command);

	if (args[0] == NULL)
	{
		free_arguments(args);
		return;
	}

	if (handle_builtin(args) == 0)
		execute_external_command(args);

	free_arguments(args);
}
