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
		return NULL;
	}

	token = strtok(command, " \t\n");
	while (token != NULL)
	{
		args[i++] = token;
		args = realloc(args, (i + 1) * sizeof(char *));
		if (args == NULL)
		{
			perror("realloc");
			return NULL;
		}
		token = strtok(NULL, " \t\n");
	}

	args[i] = NULL;
	return args;
}

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
		do
		{
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

