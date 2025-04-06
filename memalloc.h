/**
 * @file memalloc.h
 * @brief Header file for the custom memory allocator.
 * 
 * This header file defines the structures and function prototypes for a custom
 * memory allocator. The allocator provides implementations for `malloc`, `free`,
 * `realloc`, and `calloc`, as well as utilities for memory management.
 * 
 * ## Features
 * - Custom memory allocation using `sbrk`.
 * - Thread-safe operations using `pthread_mutex_t`.
 * - Memory block splitting and coalescing to reduce fragmentation.
 * - Functions to print memory statistics and layout for debugging.
 * 
 * ## Usage
 * Include this header file in your project to use the custom memory allocator.
 * Replace standard memory allocation functions with the custom ones:
 * 
 * ```c
 * #include "memalloc.h"
 * 
 * void *ptr = malloc(100);  // Allocate 100 bytes
 * free(ptr);                // Free the allocated memory
 * ```
 * 
 * ## Limitations
 * - This allocator is designed for educational purposes and may not be as
 *   efficient as standard library implementations.
 * - It uses `sbrk`, which may not be supported on all platforms.
 * 
 * ## Author
 * - Your Name (or Team Name)
 * - Date: April 6, 2025
 */

#ifndef MEMALLOC_H
#define MEMALLOC_H

#include <stddef.h>

/**
 * @brief Union representing a memory block header.
 * 
 * This union is used to store metadata for each memory block. It includes
 * information about the block's size, whether it is free, and a pointer to
 * the next block in the linked list.
 */
union Header {
    struct {
        size_t size;           /**< Size of the memory block (including header). */
        int free;              /**< Flag indicating if the block is free (1) or allocated (0). */
        union Header *next;    /**< Pointer to the next block in the linked list. */
    } s;
    alignas(max_align_t) char _align[0]; /**< Ensures proper alignment of the block. */
};

/* Function prototypes */

/**
 * @brief Allocates memory of the specified size.
 * 
 * @param size The size of the memory to allocate.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void *malloc(size_t size);

/**
 * @brief Frees a previously allocated memory block.
 * 
 * @param ptr A pointer to the memory block to free.
 */
void free(void *ptr);

/**
 * @brief Reallocates a memory block to a new size.
 * 
 * @param ptr A pointer to the memory block to resize.
 * @param new_size The new size of the memory block.
 * @return A pointer to the resized memory block, or NULL if reallocation fails.
 */
void *realloc(void *ptr, size_t new_size);

/**
 * @brief Allocates and zero-initializes memory.
 * 
 * @param num The number of elements to allocate.
 * @param size The size of each element.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void *calloc(size_t num, size_t size);

/**
 * @brief Prints the current memory statistics.
 * 
 * This function prints the total allocated and free memory to the console.
 */
void print_memory_stats(void);

/**
 * @brief Prints the memory layout.
 * 
 * This function iterates through the memory blocks and prints their
 * addresses, sizes, and free status.
 */
void print_memory_layout(void);

#endif // MEMALLOC_H
