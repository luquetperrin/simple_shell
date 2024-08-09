#include "main.h"

/**
 * prompt - Displays a prompt and waits for user input
 */
void prompt(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    printf("$ ");
    while ((nread = getline(&line, &len, stdin)) != -1)
    {
        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        execute_command(line);
        printf("$ ");
    }

    free(line);
}

/**
 * execute_command - Executes a command
 * @command: The command to execute
 */
void execute_command(char *command)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        if (execlp(command, command, (char *)NULL) == -1)
        {
            perror(command);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        while (wait(&status) != pid) {
        }
    }
}

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    prompt();
    return (0);
}
