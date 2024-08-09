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
        /* Remove the newline character at the end of the input */
        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Execute the command */
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
        /* Child process */
        if (execlp(command, command, (char *)NULL) == -1)
        {
            perror(command);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        do
        {
            waitpid(pid, &status, 0);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

/**
 * execute_file - Executes commands from a file
 * @filename: The file containing commands
 */
void execute_file(const char *filename)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&line, &len, file)) != -1)
    {
        /* Remove the newline character at the end of the input */
        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Execute the command */
        execute_command(line);
    }

    free(line);
    fclose(file);
}

/**
 * main - Entry point of the program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        /* If a filename is provided, execute commands from the file */
        execute_file(argv[1]);
    }
    else
    {
        /* Otherwise, start the interactive prompt */
        prompt();
    }
    return (0);
}
