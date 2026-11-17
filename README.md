*This project has been created as part of the 42 curriculum by ammomen.*

# Get Next Line

## Description

**Get Next Line** is a C project that implements `char *get_next_line(int fd)`, a function that returns one line at a time from a file descriptor. It works with regular files and standard input, preserving unread bytes between successive calls.

A returned line includes its terminating newline (`\n`) when present. If the last line has no newline, that line is still returned. The function returns `NULL` when no data remains or when an error occurs. The project introduces static storage duration, file-descriptor I/O, dynamic memory management, and ownership of allocated memory.

The **mandatory** implementation maintains reading state for one file descriptor at a time. The **bonus** implementation supports interleaved reads from multiple file descriptors, using only one static variable: the head pointer of a linked list of per-descriptor states.

## Instructions

### Files

The following source files belong at the repository root:

| Mandatory | Bonus |
| --- | --- |
| `get_next_line.c` | `get_next_line_bonus.c` |
| `get_next_line_utils.c` | `get_next_line_utils_bonus.c` |
| `get_next_line.h` | `get_next_line_bonus.h` |

### Compilation

There is no standalone executable in this project: `get_next_line()` is a function to link with a caller's program.

Compile the mandatory version into object files:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c \
    get_next_line.c get_next_line_utils.c
```

Compile the bonus version **separately**:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c \
    get_next_line_bonus.c get_next_line_utils_bonus.c
```

`BUFFER_SIZE` determines the maximum number of bytes requested in an individual `read()` call. It can be changed (for example, to `1` or `1024`) or omitted; the headers provide a default value of `42`. Do not link mandatory and bonus implementations together, since both define `get_next_line()`.

### Usage example

Create a temporary test program outside the submitted source files, such as `/tmp/gnl_example.c`:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc != 2)
        return (1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        /* Write the line and release caller-owned memory. */
        size_t i = 0;
        while (line[i])
            i++;
        write(STDOUT_FILENO, line, i);
        free(line);
    }
    close(fd);
    return (0);
}
```

Run it from the repository root:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -I. \
    /tmp/gnl_example.c get_next_line.c get_next_line_utils.c \
    -o /tmp/gnl_example
/tmp/gnl_example path/to/text_file.txt
```

To test the bonus, use `get_next_line_bonus.h` in the example and link only the two `_bonus.c` source files. Calls may then alternate between several open descriptors while retaining each descriptor's unread bytes.

**Memory ownership:** Every non-`NULL` returned line is separately allocated and must be freed by the caller.

## Algorithm and Design Choices

### Mandatory: dynamically resizable buffer

Instead of assuming a maximum line length or repeatedly concatenating temporary strings, the implementation uses a resizable array described by:

- `data`: pointer to the allocated byte array;
- `capacity`: total number of allocated bytes;
- `start`: index of the first unread byte;
- `end`: one past the last buffered byte.

The active unread range is `[start, end)`, with the invariant `0 <= start <= end <= capacity`.

1. **Reuse unread data.** Search the buffered range for `\n` before performing another `read()`.
2. **Reserve space.** If there is not enough contiguous space after `end`, compact the unread bytes to index zero when possible.
3. **Grow geometrically.** If compaction cannot provide enough space, allocate a larger array, normally doubling capacity until it fits the unread bytes and the next read. Copy unread bytes and free the previous array.
4. **Read and scan.** Request up to `BUFFER_SIZE` bytes, append the bytes actually received, and search the newly read portion for a newline. Repeat until a newline, EOF, or error.
5. **Extract a line.** Allocate an independent, null-terminated string containing the line (including `\n` when present); advance `start` past the returned bytes.
6. **Clean up.** Release internal storage when the buffered data is fully consumed, or on an error. At EOF, return a remaining unterminated final line before returning `NULL` on a subsequent call.

**Why this design?** A dynamic buffer handles lines whose lengths are unknown. Tracking `start` and `end` avoids shifting unread bytes after every returned line; compaction only occurs when needed. Doubling capacity reduces repeated allocation and copying: geometric growth has amortized constant-time cost per appended byte, while repeatedly increasing the capacity by a small fixed amount can require quadratic total copying for a very long line. The tradeoff is possible unused reserved capacity.

### Bonus: one static linked-list head

The bonus keeps `static t_gnl_node *head` as its **only static variable**. Each dynamically allocated node stores a file descriptor, its own `t_buffer`, and a pointer to the next node.

- On each call, search for the node matching `fd`; create an initialized node if none exists.
- Apply the same buffered reading and extraction algorithm to that descriptor's own buffer.
- Unlink and free the node and its internal buffer when its state is no longer needed or an error occurs.

A linked list uses memory for the descriptors actually encountered rather than reserving an array indexed up to the largest fd. It also avoids a predetermined descriptor limit. The tradeoff is **O(F)** lookup time for **F** tracked descriptors, compared with constant-time direct indexing for an appropriately sized array. The node is removed using a pointer-to-pointer so that unlinking the head and unlinking a middle node follow the same procedure.

**Scope:** A descriptor number can be reused by the operating system after `close()`. Like other designs that index persistent state solely by an integer fd, this implementation cannot automatically detect a close-and-reuse event if old unread bytes remain buffered. Applications should finish reading a descriptor before closing it when using this interface.

## Resources

### References

- Linux manual page, [`read(2)`](https://man7.org/linux/man-pages/man2/read.2.html) — read semantics, short reads, EOF, and errors.
- Linux manual page, [`open(2)`](https://man7.org/linux/man-pages/man2/open.2.html) — obtaining file descriptors.
- Linux manual page, [`close(2)`](https://man7.org/linux/man-pages/man2/close.2.html) — descriptor lifetime and reuse.
- Linux manual pages, [`malloc(3)`](https://man7.org/linux/man-pages/man3/malloc.3.html) and [`free(3)`](https://man7.org/linux/man-pages/man3/free.3.html) — dynamic memory allocation and release.
- *The C Programming Language*, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie — pointers, structures, and storage classes.
- 42 **Get Next Line** subject, version 14.3 — project contract, restrictions, and bonus requirements.

### AI usage disclosure

AI (ChatGPT) was used as a **learning and development aid** during this project:

- **Conceptual learning:** explanations and questions about `read()`, short reads, EOF, static variables, pointer arithmetic, double pointers, ownership, and dynamic arrays.
- **Design:** discussion of alternatives and tradeoffs before selecting a resizable buffer with compaction and geometric growth, and a linked list for bonus descriptor state.
- **Implementation assistance:** reviewing and debugging C code; providing example implementations and integration guidance for parts of the bonus, including descriptor-node management and the bonus `get_next_line()` logic.
- **Verification and documentation:** suggestions for testing buffer sizes, memory safety, multiple descriptors, and edge cases; assistance drafting this README against the subject requirements.

The implementation was studied and tested as part of the project workflow. AI suggestions are not a substitute for understanding the code or independently validating its behavior.
