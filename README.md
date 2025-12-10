# get_next_line – 42 Project

## Overview
`get_next_line` is a function that reads from a file descriptor and returns one line at a time.  
Each call returns the next line, including the newline character.  
It supports any valid file descriptor, including standard input.

---

## Key Features

- Reads input **line-by-line**
- Works with any file descriptor (`fd = 0, 1, 2, ...`)
- Handles **BUFFER_SIZE variation**
- Robust memory management (no leaks)
- **Bonus:** supports multiple file descriptors simultaneously  
  using only **one static variable** (linked-list implementation)

---

## Compilation & Usage

### Mandatory
```bash
make

## Test with your own file
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
./a.out

## Project Structure
>>>>>>> f5bd31d (Implement get_next_line and bonus)
get_next_line/
│
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
└── Makefile
