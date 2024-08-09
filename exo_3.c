#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 100

/* Function prototypes */
void handle_command(char *line);

/**
 * main - Entry point for the shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("#cisfun$ ");

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				free(line);
				exit(0);
			}
			else
			{
				perror("getline");
				continue;
			}
		}

		line[strcspn(line, "\n")] = '\0';

		handle_command(line);
	}

	free(line);
	return (0);
}

/**
 * handle_command - Parses and executes a command
 * @line: The command line to be parsed and executed
 *
 * Description: This function tokenizes the input line and uses fork and execvp
 * to execute the command in a child process.
 */
void handle_command(char *line)
{
	char *args[MAX_ARGS];
	int i;

	i = 0;
	args[i] = strtok(line, " ");
	while (args[i] != NULL && i < MAX_ARGS - 1)
	{
		i++;
		args[i] = strtok(NULL, " ");
	}
	args[i] = NULL;

	if (args[0] != NULL)
	{
		if (fork() == 0)
		{
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}
}
