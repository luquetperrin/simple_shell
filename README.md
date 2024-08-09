# Simple Shell

## Overview
This project is a basic implementation of a UNIX shell. It emulates the behavior of the traditional command-line interpreter, allowing users to execute commands both interactively and non-interactively. The shell handles fundamental tasks such as parsing user input, creating processes, and executing commands. 

The project was developed as part of the ALX SE program, and it demonstrates our understanding of key concepts in C programming, UNIX system calls, and process control.

## Features
- **Interactive Mode**: The shell displays a prompt and waits for the user to enter a command. After execution, the prompt is displayed again.
- **Non-Interactive Mode**: The shell reads and executes commands from a file or a pipe, then exits.
- **Command Execution**: The shell searches for executable files in the directories listed in the `PATH` environment variable.
- **Error Handling**: Proper error messages are displayed when commands are not found or cannot be executed.
- **Built-in Commands**: Supports built-in commands like `exit` to terminate the shell.

## Requirements
- **OS**: Ubuntu 20.04 LTS
- **Compiler**: `gcc` with the following options:
  ```bash
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
