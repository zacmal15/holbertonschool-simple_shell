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

## Using our shell
### Parentel Guidance
Upon compiling the code, when you run the executable, the user will be greeted with the prompt
```
(good_boy$)
```
which comes from the infinite loop where interactive mode is initiated with the command
```
isatty(STDIN_FILENO)
```
The user, who we will refer to from now on as "the good boy", can input basic commands in a direct path form:
```
/bin/ls
```
or as arguments:
```
ls -l
```
The input will be read and the input line counted, and the parser tokenises the input as explained above.

If the input is a builtin, we handle this in the parent before they fork to make babies.

### A child has been forked
The shell is now ready to execute the command.

The code checks checks if the command exists. If not, the shells spits back at the good boy with an error message and a child isnt forked.

If the command is real, then we can start the child process with:
```
pid = fork()
```
The PID simply differentiates between processes by assigning a unique ID to each program so if you run the same command 10 times, each iteration will habe its own PID.

If the child forks successfully, the child can run the program and execute the good boy's command:
```
execve(path, argv[0], environ)
```
This replaces the child with the program for the path the good boy wants the shell to use (does this mean the shell is the obedient little good boy???)

The parent must wait for the child to finish its tasks and the exit status of the PID will be checked and if the child exits normally then the status is returned with its exit code.

The child is now free to ***die***

### Upon the death of a child
The parent process starts up again, looping back round to the start of the infinite loop

The shell can be exitted if the good boy so pleases, by typing the builtin command
```
(good_boy$)  exit
```
And thats all i have to say about that.

## Acknowledgements
Code written (wrote???) by Sam Thompson and Zac Malkoun under expert supervision of a rubber duck and Monsieur Jonathan Clus, merci beaucoup mon ami!

Also thank you to another Monsieur Thomas Yamini who has returned back to the land of croissants and smelly cheeses, gbnf.

Pull requests are allowed on the condition that you hide the comment "Mo Salah Egyptian King" somewhere.

Ok thank you byyeeeee
