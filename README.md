# holbertonschool-simple shell

## Description

This repo contains work relating to the simple shell project including:

- Bringing up a new shell displaying a prompt
- Allowing user to type a command
- Printing error messages if command is not executable
- Handling errors
- Handling EoF condition (Ctrl + D)
- Work with lines with arguments
- Handle the PATH, not calling fork if it doesnt exist
- Implemented 'exit'
- Use the __env__ built-in to print the environment

Written by Sam Thompson and Zac Malkoun

---

## Compilation

Compiles files using gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh to compile the files.

---

## Requirements

- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)

---

## Files present
### main.h

Contains necessary libraries and function prototypes.

Notable line is:
```
extern char **environ
```
which programs acces to the process environment list.
