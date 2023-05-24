main: The main entry point of the program. It sets up a loop to read commands from the user and calls the execute_command function to execute each command.

execute_command: Executes the given command by forking a child process and calling handle_arguments in the child process. It waits for the child process to finish in the parent process.

handle_arguments: Handles the command arguments by parsing them, checking if it's a built-in command using handle_builtin, and executing the command using execute_external_command if it's not a built-in command.

handle_PATH: Handles the PATH environment variable. It checks if the specified command exists and is executable. If so, it uses execve to execute the command. If not, it displays an error message and exits.

shell_exit: Exits the shell by displaying an exit message and calling exit(0).

handle_env: Handles the environment variables. It iterates through the environ array, which contains the environment variables, and writes each variable to the standard output.

parse_arguments: Parses the command string into individual arguments. It tokenizes the command string using spaces, tabs, and newline characters as delimiters and stores the arguments in a dynamically allocated array.

free_arguments: Frees the memory allocated for the arguments array.

handle_builtin: Handles the built-in commands. It checks if the first argument is a built-in command (e.g., "exit" or "env"). If it is, it executes the corresponding built-in function (shell_exit or handle_env). It returns 1 if the command is built-in and 0 otherwise.

execute external command: Executes an external command by forking a child process and using execvp to execute the command. It waits for the child process to finish in the parent process.

These functions work together to implement a basic shell that can execute commands, handle built-in commands, handle environment variables, and exit the shell when requested.i
