#include "shell.h"

/**
 * shell_exit - Exit the shell
 *
 * Return: No return value
 */
void shell_exit(void)
{
	write(STDOUT_FILENO, "Exit shell\n", 11);
	exit(0);
}
