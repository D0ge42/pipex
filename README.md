
# Pipex - 42 School Project

## Description

**Pipex** is a project at 42 school where the goal is to implement a simple version of the shell piping mechanism. You will create a program that simulates how commands are executed in a pipeline, chaining multiple processes together through pipes.

In this project, you'll:
- Use pipes to transfer output from one process to the input of another.
- Handle multiple commands and arguments.
- Implement proper error handling for invalid commands or arguments.

### Objectives:
- Implement a program that mimics the behavior of pipes in a shell.
- Create a chain of processes where the output of one command becomes the input for the next.
- Handle multiple commands, arguments, and process management using `fork()`, `exec()`, and `pipe()` system calls.

---

## Requirements

- Use the `fork()` system call to create processes.
- Use the `execve()` system call to execute commands.
- Handle pipes with the `pipe()` system call to connect the input/output between processes.
- Properly handle file descriptors (stdin, stdout).
- Implement error handling for invalid commands and arguments.
- Ensure that resources are properly cleaned up and no memory leaks occur.

---

## Usage

### Compilation

To compile the project, run the following command:

```bash
make
```

This will compile the source files and generate the `pipex` executable.

### Running the program

To run the program, use the following format:

```bash
./pipex file1 cmd1 arg1 ... cmd2 arg2 ... file2
```

Where:
- `file1`: The input file from which the first command will read.
- `cmd1 arg1 ...`: The first command and its arguments to execute.
- `cmd2 arg2 ...`: The second command and its arguments to execute.
- `file2`: The output file where the last command's output will be written.

---

## Example

For example, you can run the following:

```bash
./pipex input.txt "cat" "grep search" output.txt
```

This will:
- Read from `input.txt`.
- Use the `cat` command to display the file’s contents.
- Pipe the output of `cat` to `grep search` to filter the lines containing "search".
- Write the resulting output to `output.txt`.

---

## Project Structure

```
├── Makefile          # Build file to compile the project
├── libft             # functions library.
├── pipex.c           # Main program file
├── pipex.h           # Header file containing function prototypes and includes
└── utils.c           # Utility functions
```

---

## Testing

Test your program with different commands, files, and edge cases to ensure all the following scenarios are handled:

- Invalid commands.
- Multiple commands chained together.
- Files that do not exist or are not readable.
- Permissions errors when reading from or writing to files.

---

## Contributors

- [Your Name](https://github.com/D0ge42)
