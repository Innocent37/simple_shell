#include "shell.h"

/**
 * handle_PATH - Handle the PATH environment variable
 *
 * Return: No return value
 */
void handle_PATH(char **args)
{
	if (access(args[0], X_OK) == 0)
	{
		execve(args[0], args, environ);
	}
	else
	{
		char error_msg[] = "No such file or directory\n";

		write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
		exit(EXIT_FAILURE);
	}
}
