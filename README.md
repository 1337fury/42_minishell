# 42 Minishell

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Command Syntax](#command-syntax)
- [Built-in Commands](#built-in-commands)
- [File Redirection](#file-redirection)
- [Pipeline](#pipeline)
- [Environment Variables](#environment-variables)
- [Signal Handling](#signal-handling)
- [Error Handling](#error-handling)

## Introduction

42 Minishell is a simple Unix shell implementation developed as part of the curriculum at 42. It provides a command-line interface that allows users to execute commands, launch programs, and perform various operations in a shell environment.

The primary goal of this project is to gain a deeper understanding of how shells work by implementing key features and functionalities found in popular Unix shells such as bash or zsh.

## Features

- Command execution and program launching.
- Support for built-in commands.
- Execution of external commands.
- File redirection for input/output.
- Pipeline execution.
- Background command execution.
- Environment variable management.
- Signal handling for interrupt and termination signals.
- Error handling and error messages.

## Installation

To use 42 Minishell, follow these steps:

1. Clone the repository to your local machine:

   ```shell
   git clone https://github.com/1337fury/42_minishell.git
   ```

2. Change into the project directory:

   ```shell
   cd 42_minishell
   ```

3. Build the minishell binary using the provided Makefile:

   ```shell
   make
   ```

   This will compile the source code and generate the `minishell` executable.

4. Run the minishell:

   ```shell
   ./minishell
   ```

   Now you can start using the minishell!

## Usage

Once you have started the minishell, you can enter commands to execute and interact with the shell environment.

```shell
$ ls -l
$ echo "Hello, world!"
$ cd /path/to/directory
$ pwd
```

Use the `exit` command to exit the minishell.

```shell
$ exit
```

## Command Syntax

The command syntax in 42 Minishell generally follows the syntax of most Unix shells. A command typically consists of the command name followed by arguments and options.

```shell
command [arguments...] [options...]
```

Some commands may have additional syntax rules, which are explained in the corresponding sections below.

## Built-in Commands

42 Minishell supports several built-in commands:

- `echo` - Display a line of text.
- `cd` - Change the working directory.
- `pwd` - Print the current working directory.
- `export` - Set environment variables.
- `unset` - Unset environment variables.
- `env` - List all environment variables.
- `exit` - Exit the minishell.

## File Redirection

42 Minishell supports file redirection for input and output. You can redirect the standard input or output of a command to a file.

The following redirection operators are supported:

- `<` - Redirect standard input from a file.
- `>` - Redirect standard output to a file (overwriting the file if it exists).
- `>>` - Redirect standard output to a file (appending to the file if it exists).

## Pipeline

42 Minishell allows you to connect multiple commands together in a pipeline, where the output of one command serves as the input to the next command.

To create a pipeline, use the `|` (pipe) operator:

```shell
$ command1 | command2 | command3
```

## Environment Variables

42 Minishell allows you to manage environment variables. You can set, unset, and list environment variables using the built-in commands `export`, `unset`, and `env`, respectively.

## Signal Handling

42 Minishell provides basic signal handling. It can handle interrupt (SIGINT) and termination (SIGQUIT) signals, allowing you to gracefully terminate running commands.

## Error Handling

42 Minishell performs error handling and displays appropriate error messages when encountering errors such as command not found, syntax errors, file not found, and others.