*This project has been created as part of the 42 curriculum by [maryaada], [walneama].*

# Description

### What is Minishell?
Minishell is a 42 project written in C where it's a simple and "mini" recreation of the Bash shell existing within Linux and Unix operating systems, it follows the behaviour of regular Bash and allows the user to navigate, interact and manipulate files and directories the same way regular Bash would allow.

### What is shell?

A shell is a program that acts as the middleman between the user and the operating system's kernel. Rather than interacting with the system directly, the user types commands into the shell, which interprets them and asks the kernel to carry them out, whether that's running a program, moving files around, or managing processes. Bash (Bourne Again Shell) is one of the most widely used shells on Linux and Unix systems, and it's the one Minishell takes its behaviour from.

## Project Workflow
Every command entered into Minishell passes through the following stages:

```mermaid
flowchart LR
    A[User Input] --> B[Tokenizer / Lexer]
    B --> C[Syntax Validation]
    C --> D[Parser]
    D --> E[Built-ins / Execution]
```
- User Input: upon running the minishell program, the user is expected to write out instructions as commands as they see fit to their need. This is seen as a single string and not separate commands and files.

- Tokeniser/Lexer: Here our program begins to splice through the string weaving in between white spaces to identify every non-white space character as a separate split string i.e Tokens, ready to be validated as commands or errors.

- Syntax Validation: Here is where the tokens are then further split into commands, files, pipes, redirections each within their own struct in the code. As the raw string tokens are validated they are categorised with enums of their types.

- Parser: The parser's job is to take each saved token and their types and send it to the correct function that will carry out the main job of the shell i.e execution of the command.

- Builtins and Execution: The main job of the minishell, this is where the parsed commands are finally carried out. Builtins such as `cd`, `echo`, `pwd`, `export`, `unset`, `env`, and `exit` are handled directly within the program itself, while any other command is searched for in the system's PATH and executed as an external process using `execve`. Pipes and redirections are set up beforehand so that input and output are correctly routed between commands, just as they would be in Bash.

- Signal Handling: Minishell also replicates Bash's behaviour when it comes to signals. Pressing `ctrl-C` interrupts the current line and starts a fresh prompt, `ctrl-D` exits the shell when the input line is empty, and `ctrl-\` is ignored in interactive mode just as it is in Bash. These signals are handled differently depending on whether the shell is idle at the prompt, waiting on a child process, or reading a heredoc, so each state has its own signal behaviour to stay consistent with how Bash would respond.

## Lexer (Tokenization)

The lexer is responsible for transforming the raw input string into a sequence of tokens. Instead of processing the entire command as plain text, the lexer identifies meaningful elements such as:

- words
- pipes (|)
- input redirections (<)
- output redirections (>)
- append redirections (>>)
- heredocs (<<)


## Instructions

To run minishell you should run
```bash
make && make clean
```

That should create a program called "minishell" and clean all the object files from view.

next run
```bash
./minishell
```

Great! Now you're inside of our minishell!

Follow the evaluation sheet and run commands as instructed or below are some examples of commands to run that were implemented by us according to the project rubric.

### Basic Commands
```bash
echo "Hello World"
pwd
ls -l
```

### Builtins
```bash
cd /tmp
cd ..
export MY_VAR="hello"
env
unset MY_VAR
exit
```

### Pipes
```bash
ls -l | grep minishell
cat file.txt | wc -l
echo "hello" | tr a-z A-Z | rev
```

### Redirections
```bash
echo "hello" > output.txt
cat < output.txt
echo "world" >> output.txt
cat << EOF
this is a heredoc
EOF
```

### Variable Expansion
```bash
echo $HOME
echo "User is $USER"
echo $?
```

### Combined Examples
```bash
cat file.txt | grep "hello" > result.txt
echo $PATH | tr ':' '\n'
ls -l | sort | head -5
```

## Your minishell should look like this

```text
┌──────────────────────────────────────────────┐
│ ●  ●  ●             Terminal                 │
├──────────────────────────────────────────────┤
│ maryaada@lab2r3s14:~/minishell$ make         │
│ cc -Wall...                                  │
│ ....                                         │
│                                              │
│ maryaada@lab2r3s14:~/minishell$ ./minishell  │
│ minishell$ pwd                               │
│ /home/maryaada/minishell                     │
│ minishell$                                   │
└──────────────────────────────────────────────┘
```