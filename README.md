get_next_line – 42 Project
📘 Overview

get_next_line is a function that reads from a file descriptor and returns one line at a time.
Each call returns the next line, including the newline character.
It supports any valid file descriptor, including standard input.

🧠 Key Features

Reads input line-by-line

Works with any file descriptor (fd = 0,1,2,...)

Handles BUFFER_SIZE variation

Robust memory management (no leaks)

Bonus: supports multiple file descriptors simultaneously
using only one static variable (linked-list implementation)

🚀 Compilation & Usage
Mandatory
make

Bonus
make bonus

Test with your own file
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
./a.out

🏗️ Project Structure
get_next_line/
│
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line_bonus.c
├── get_next_line_utils_bonus.c
├── get_next_line.h
├── get_next_line_bonus.h
└── Makefile

🔧 Implementation Details
How it works

The function keeps a static buffer that stores data between calls.
It continues reading until:

A newline \n is found

Or EOF is reached

After that:

The line is extracted and returned

The remaining buffer is stored for the next call

Memory is freed correctly to avoid leaks

Internal Components
read_to_newline()

Reads from fd and appends to the buffer using ft_strjoin

Stops when a newline appears or EOF occurs

extract_line()

Returns the string up to and including the newline

extract_rest()

Saves leftover data for the next call

Bonus Linked List

One static pointer (static t_fdnode *head)

Each node stores:

fd

backup

next

Allows simultaneous reading from multiple descriptors

🧪 Testing
Valgrind (Memory Leak Check)
valgrind --leak-check=full ./a.out

Recommended Tests

Multiple lines

Last line without newline

BUFFER_SIZE = 1 / 10 / 1000

Multiple file descriptors (bonus)

Standard input (fd = 0)

Non-existent file / invalid fd

🧱 Learned Skills

Low-level file I/O (read)

Memory allocation & leak prevention

Manual string manipulation

Static variables & state management

Linked list design (bonus)

Handling multiple file descriptors

Clean separation of functional responsibilities
