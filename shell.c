#include "shell.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char *command = NULL;
	size_t bufsize = 0;
	ssize_t bytes_read;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		bytes_read = getline(&command, &bufsize, stdin);
		if (bytes_read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		execute_command(command);
	}

	free(command);
	return (0);
}

/**
 * execute_command - Execute the given command
 * @command: The command to execute
 *
 * Return: No return value
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		handle_arguments(command);
		exit(0);
	}
	else
	{
		wait(&status);
	}
}

/**
 * execute_external_command - Execute an external command
 * @args: The arguments array
 *
 * Return: No return value
 */
void execute_external_command(char **args)
{
	pid_t child_pid, wait_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		do {
			wait_pid = waitpid(child_pid, &status, WUNTRACED);
			if (wait_pid == -1)
			{
				perror("waitpid");
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

