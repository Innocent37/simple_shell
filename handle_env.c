#include "shell.h"

/**
 * handle_env - Handle the environment variables
 *
 * Return: No return value
 */
void handle_env(void)
{
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
