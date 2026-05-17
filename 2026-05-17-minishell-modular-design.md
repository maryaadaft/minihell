# Minishell Modular Design Specification

## 1. Overview
This document outlines the architecture for Minishell, a 42 school project to recreate a simple bash-like shell. The project will focus strictly on the mandatory requirements and will be built in a highly modular fashion to allow for independent testing and robust development.

## 2. Architecture & Modules
The shell is divided into 6 distinct, sequential modules. 

### 2.1 The Environment Module (`env`)
*   **Purpose:** Converts the system's `char **envp` into a mutable Linked List at startup.
*   **Responsibilities:** 
    *   Initialize the environment linked list.
    *   Provide getters for variable values (e.g., `get_env_val(char *key)`).
    *   Handle `export` (add/update variables).
    *   Handle `unset` (remove variables).
    *   Maintain the special `$?` variable (last command exit status).

### 2.2 The Lexer Module (`lexer`)
*   **Purpose:** Tokenizes the raw input string from `readline`.
*   **Input:** Raw `char *` string.
*   **Output:** A Linked List of Tokens.
*   **Responsibilities:** 
    *   Identify words, pipes (`|`), redirections (`<`, `>`, `<<`, `>>`), and quotes.
    *   Categorize input chunks without validating grammatical correctness.
    *   Quotes are identified but *not* removed at this stage.

### 2.3 The Parser Module (`parser`)
*   **Purpose:** Validates syntax and organizes tokens into a flat list of commands.
*   **Input:** The Token Linked List.
*   **Output:** A Linked List of Commands (`t_cmd`).
*   **Responsibilities:** 
    *   Check for syntax errors (e.g., consecutive pipes, missing redirection targets).
    *   Group words into a `char **args` array for `execve`.
    *   Attach a list of redirections (`t_redir`) to each specific command.

### 2.4 The Expander Module (`expander`)
*   **Purpose:** Expands variables and handles quote removal prior to execution.
*   **Input:** The parsed Command List.
*   **Responsibilities:** 
    *   Replace `$VAR` with its corresponding value from the Environment Module.
    *   Expand `$?` to the exit status.
    *   Remove outer single `''` and double `""` quotes, applying bash quoting rules (variables do not expand in single quotes).

### 2.5 The Executor Module (`exec`)
*   **Purpose:** Executes the prepared Command List.
*   **Input:** The fully expanded Command List.
*   **Responsibilities:** 
    *   Iterate through the pipeline.
    *   Set up pipes (`pipe()`) between commands.
    *   Fork child processes (`fork()`).
    *   Apply redirections using `dup2()`.
    *   Execute commands by either calling the internal Built-ins module or finding the binary in `$PATH` and calling `execve`.
    *   Wait for children and update the `$?` status.

### 2.6 The Built-ins Module (`builtins`)
*   **Purpose:** Implement mandatory shell built-in commands.
*   **Responsibilities:** 
    *   `echo` (with `-n` flag).
    *   `cd` (relative and absolute paths).
    *   `pwd`.
    *   `export`.
    *   `unset`.
    *   `env`.
    *   `exit`.

## 3. Project Structure
The repository will be structured to isolate modules and their corresponding tests.

```text
minishell/
├── src/
│   ├── env/
│   ├── lexer/
│   ├── parser/
│   ├── expander/
│   ├── exec/
│   └── builtins/
├── includes/
│   └── minishell.h
└── tests/
    ├── test_env.c
    ├── test_lexer.c
    └── test_parser.c
```

## 4. Testing Strategy
*   **Framework:** Custom C test drivers using standard `assert()`.
*   **Approach:** Each module will have a corresponding `test_<module>.c` file in the `tests/` directory. These files will contain their own `main()` functions to feed predefined inputs into the module functions and assert the expected outputs or structural states. No external testing frameworks will be used to comply with 42 norms.
