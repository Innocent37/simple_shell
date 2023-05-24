#include "shell.h"

/**
 * free_arguments - Free the memory allocated for the arguments
 * @args: The arguments array
 *
 * Return: No return value
 */
void free_arguments(char **args)
{
	if (args != NULL)
	{
		free(args);
	}
}
