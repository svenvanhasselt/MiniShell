
# MiniShell

MiniShell is a simple Unix shell implemented in C, developed as part of the 42 Network curriculum at Codam Coding College. It aims to replicate basic functionalities of the Bash shell, providing a minimalistic environment for command execution.

## Features

- **Command Execution**: Execute binaries from absolute, relative, or environment paths (e.g., `/bin/ls` or `ls`).
- **Built-in Commands**: Includes built-in implementations of common commands such as `echo`, `pwd`, `cd`, `env`, `export`, `unset`, and `exit`.
- **Pipes and Redirections**: Supports input/output redirection (`>`, `>>`, `<`) and piping (`|`) between commands.
- **Environment Variables**: Handles environment variables, including expansions like `$HOME` and the return code `$?`.
- **Signal Handling**: Manages signals like `Ctrl-C` to interrupt and `Ctrl-\` to quit a program, as well as `Ctrl-D` to send an EOF signal, similar to Bash behavior.

## Installation

To build MiniShell, ensure you have `make` and a C compiler installed. Then, run:

```bash
make
```

This will compile the source code and generate the `minishell` executable.

## Usage

Start MiniShell by running:

```bash
./minishell
```

You can then enter commands as you would in a standard shell. For example:

```bash
$ echo "Hello, World!"
Hello, World!
$ ls -l | grep minishell
-rwxr-xr-x 1 user group 12345 Jan 28 18:40 minishell
$ export MY_VAR="Test"
$ echo $MY_VAR
Test
```

## Project Structure

- `includes/`: Header files.
- `library/`: External libraries used in the project.
- `libft/`: Custom implementations of standard C library functions.
- `source/`: Source code files.
- `Makefile`: Build configuration.


