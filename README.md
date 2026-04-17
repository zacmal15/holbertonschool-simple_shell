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

### main.c

Contains the infinite loop which prints the prompt:
```
(good_boy$)  
```
because whoever types is very obedient and i guess the shell is too.

Function then reads the line inputted, counts the line, performs some cleanup and asks the child to execute the function. All being well, the child is killed and we return to the _good\_boy$_ prompt.

### shell.c

This file has the **execute_command()** function.

Here we create the PID, fork children and wait for them to die. Errors are returned if the fork fails, commands arent found or the PID = 0. **waitpid()** is used to stop the parent from running new commands and we get returned the exit code, or 1 if the child is killed abnormally.

### parser.c

Splits the input into commands and arguments. we use **strtok()** to separate elements into an array. for example if we type
```
ls -l -t
```
it splits into 3 elements in an array, plus a null terminator
```
argv[0] = "ls"
argv[1] = "-l"
argv[2] = "-t"
argv[3] = "/0"
```
### utils.c
This contains useful functions to print the prompt, handle the end of file confition (maybe not used) and to clean\_input to remove newline from the input string by replacing with a null byte.

### builtins.c
This file contains the built-in functions such as printing the environment, and exiting the shell.

This file contains the built-in function for printing the current environment, etc:
```
(good_boy$) env
```
Output should be:
```
PATH=/usr/bin:/bin
HOME=/home/user
USER=user
...
```
This file also contains the built-in exit, etc:
```
(good_boy$) exit
```
This command should exit the interactive shell mode.

### find\_command.c
First function gets the path from the environment by strncmp to PATH=.

find\_command first checks for a direct path case with '/' and then duplicates if it exists.

If not, getpath is ran to locate the **PATH** inside the environment and copys this path.

**strtok()** is used again to split into directories per colon ie:
```
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin
```
will split into:
```
/usr/local/sbin
/usr/local/bin
/usr/sbin
```
memory is allocated for the tokens and the original command plus more for the null byte.

If it all works proper, the full path is returned and confirms that the command exists on the path.

## Going through each task
