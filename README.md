# memalloc

A custom implementation of memory allocation functions in C using the `sbrk` Unix kernel syscall. This project provides a robust and educational approach to understanding memory management by implementing `malloc`, `free`, `realloc`, and `calloc` from scratch. It also includes utilities for debugging and demonstrates usage in various data structures.

## Features

- **Custom Memory Allocation**: Implements memory allocation using `sbrk`.
- **Thread-Safe Operations**: Ensures safe usage in multithreaded environments with `pthread_mutex_t`.
- **Memory Management**: Supports splitting and coalescing memory blocks to reduce fragmentation.
- **Debugging Utilities**: Provides functions to print memory statistics and layout.
- **Standard Functions**: Implements `malloc`, `free`, `realloc`, and `calloc`.

## Future Enhancements

- **Improved Fragmentation Handling**: Reduce memory fragmentation for better performance.
- **Optimized `sbrk` Usage**: Enhance performance by minimizing system calls.
- **Advanced Debugging Tools**: Add visualization tools for memory layout and usage.

## Prerequisites

- **Make**: Version 4.4.1 or higher.
- **GCC**: Version 14.1.1 or higher.
- **Unix-based System**: The project uses `sbrk`, which is not supported on Windows.

## Build and Run

### Compiling the Project
To compile the project, use the `make` command:
```bash
make
```

### Running Examples
To run any of the examples, use the following command:
```bash
make <example_name>
```
For example:
```bash
make linked_list
```


## Example Usage

### Linked List Example
The `linked_list.c` file demonstrates how to use the custom allocator to manage memory for a linked list:
```c
list push(list *root, int val) {
    list new_node = (list)malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = *root;
    *root = new_node;
    return new_node;
}
```

### Binary Tree Example
The `binary_tree.c` file shows how to use the custom allocator for a binary tree:
```c
tree insert(tree *root, int val) {
    if (!(*root)) {
        *root = malloc(sizeof(Node));
        (*root)->val = val;
        (*root)->right = NULL;
        (*root)->left = NULL;
        return *root;
    }
    // ...existing code...
}
```


## Acknowledgments

- Inspired by the need to understand low-level memory management.
- Special thanks to the open-source community for providing valuable resources.
