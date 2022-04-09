# minishell

As beautiful as shell.

## Intro

This project aims to replicate as closely as possible some of the main features of bash. This is not an exact replica and there are a lot of thing that wont work or may not work the same as in bash.

## How to run
---
### Clone the repo
```
git clone https://github.com/diegosanchezstrange/minishell.git minishell
```
### Install dependencies

Install the readline library

#### Linux

Debian based platforms:
```
sudo apt install libreadline-dev
```
Arch based platforms:
```
sudo pacman -S readline
```
#### Mac os
```
brew install readline
```
### Compile and execute
```
cd minishell
make
./minishell
```

## Features
- Execute a shell in interactive mode.
- Interpret commands searching for the right executable in PATH.
- Implement the following builtins:
    - echo 
    - cd
    - pwd
    - env
    - export
    - unset
    - exit
- Interpret "" and '' inhibiting all interpretation of a sequence of characters.
- Working command history
- Redirecctions (>, >>, <<, <)
- Pipes ( | )
- Expanding enviroment variables and $? expands the last exit code
- ctrl-C, ctrl-D and ctrl-\ work like in bash 

