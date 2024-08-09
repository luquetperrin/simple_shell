#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - Entry point for the shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("#cisfun$ ");

		read = getline(&command, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				free(command);
				exit(0);
			}
			else
			{
				perror("getline");
				continue;
			}
		}

		command[strcspn(command, "\n")] = '\0';

		if (fork() == 0)
		{
			execlp(command, command, NULL);
			perror("execlp");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}

	free(command);
	return (0);
}
