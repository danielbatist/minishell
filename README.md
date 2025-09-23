# Minishell - 42 Project

**Minishell** is a project from the 42 curriculum that we developed together.  
Our goal was to build a simplified version of a Unix shell, capable of parsing and executing commands while handling pipes, redirections, and environment variables.  

Working on this project gave us a deeper understanding of how shells work internally, and it was also a great exercise in collaboration and teamwork.

## Key Learnings

- **Process Management:** We learned how to use `fork`, `execve`, and `wait` to create and control processes.  
- **Pipes & Redirections:** We implemented inter-process communication with pipes and managed input/output redirections.  
- **Parsing & Lexing:** We built a parser to handle complex command inputs, including quotes and operators.  
- **Environment Variables:** We gained experience managing environment variables and exporting/updating them dynamically.  
- **Signals:** We handled system signals (`CTRL+C`, `CTRL+D`, `CTRL+\`) to mimic the behavior of real shells.  
- **Teamwork:** We practiced dividing responsibilities, reviewing code, and making decisions together, which strengthened our collaboration skills.  

## Features

- Execute simple commands with arguments.  
- Support for multiple pipes and redirections.  
- Manage environment variables with `export` and `unset`.  
- Built-in commands such as `cd`, `echo`, `pwd`, `env`, `exit`.  
- Proper signal handling for a shell-like experience.  

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/danielbatist/minishell.git
cd minishell
```
2. Compile the program:

```bash
make
```

3. Run the shell:

```bash
  ./minishell
```

Thank you for checking out our Minishell project.
This project was an incredible opportunity to dive deeper into system programming in C, while also learning the value of teamwork and communication when building complex software.
