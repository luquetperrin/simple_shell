#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */
void prompt(void);
void execute_command(char *command);
void execute_file(const char *filename);

#endif /* MAIN_H */
