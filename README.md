*This project has been created as part of the 42 curriculum by [maryaada], [walneama].*

# Description
Minishell is ...

A shell is ...


## Project Workflow
Every command entered into Minishell passes through the following stages:

```
User Input 
     │
     ▼
Tokenizer (Lexer)
     │
     ▼
Syntax Validation
     │
     ▼
Parser
     │
     ▼
Built-ins / Execution
     │
     ▼
Operating System
```

## Lexer (Tokenization)

The lexer is responsible for transforming the raw input string into a sequence of tokens. Instead of processing the entire command as plain text, the lexer identifies meaningful elements such as:

- words
- pipes (|)
- input redirections (<)
- output redirections (>)
- append redirections (>>)
- heredocs (<<)
