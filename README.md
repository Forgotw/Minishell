# **Minishell**

**Minishell** is a project from the École 42 curriculum, where you build your own shell program. The project aims to strengthen your understanding of process management, file descriptors, and UNIX system calls, while encouraging the implementation of additional features to replicate real shell behavior.

---

## **Overview**

Minishell is a simplified version of a UNIX shell, designed to execute commands and manage input/output operations. It supports:
- Interactive command execution.
- Redirections (`>`, `>>`, `<`).
- Pipes (`|`).
- Signal handling (e.g., `Ctrl-C`, `Ctrl-\`, `Ctrl-D`).
- Environmental variable management (`export`, `unset`, `env`).
- Advanced features:
  - Wildcards (`*`).
  - Logical operators (`&&`, `||`).
  - Subshells (`()`).

---

## **Features**

### **Mandatory Features**
- **Built-in Commands**:
  - `echo`: Print text to standard output.
  - `cd`: Change directory.
  - `pwd`: Print the current working directory.
  - `export`: Set environment variables.
  - `unset`: Remove environment variables.
  - `env`: Display environment variables.
  - `exit`: Terminate the shell.

- **Redirections**:
  - Output redirection: `>` and `>>`.
  - Input redirection: `<`.

- **Pipes**:
  - Chain commands with `|` to pass output as input to the next command.

- **Signal Handling**:
  - Properly handle `Ctrl-C`, `Ctrl-\`, and `Ctrl-D` signals.

### **Bonus Features**
- **Wildcards (`*`)**:
  - Match multiple files or directories in a path.

- **Logical Operators (`&&`, `||`)**:
  - `&&`: Execute the next command only if the previous one succeeds.
  - `||`: Execute the next command only if the previous one fails.

- **Subshells (`()`)**:
  - Group commands to be executed in a subshell environment.
