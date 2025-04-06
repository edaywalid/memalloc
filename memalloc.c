#include "./memalloc.h"
#include "stdlib.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

union Header *head = NULL, *tail = NULL;

size_t total_allocated = 0;
size_t total_free = 0;

void update_memory_stats() {
    total_allocated = 0;
    total_free = 0;
    union Header *current = head;
    while (current) {
        if (current->s.free) {
            total_free += current->s.size;
        } else {
            total_allocated += current->s.size;
        }
        current = current->s.next;
    }
}

void print_memory_stats() {
    update_memory_stats();
    printf("Total Allocated: %zu bytes\n", total_allocated);
    printf("Total Free: %zu bytes\n", total_free);
}

void print_memory_layout() {
  union Header *current = head;
  printf("Memory Layout:\n");
  while (current) {
      printf("Block at %p | Size: %zu | Free: %d\n", (void *)current, current->s.size, current->s.free);
      current = current->s.next;
  }
}



size_t align(size_t size, size_t alignment) {
    return (size + alignment - 1) & ~(alignment - 1);
}

union Header *find_free_block(size_t bsize) {
  union Header *current = head;
  while (current) {
      if (current->s.free && current->s.size >= bsize) {
          if (current->s.size > bsize + sizeof(union Header)) {
              union Header *new_block = (union Header *)((char *)current + bsize + sizeof(union Header));
              new_block->s.size = current->s.size - bsize - sizeof(union Header);
              new_block->s.free = 1;
              new_block->s.next = current->s.next;

              current->s.size = bsize;
              current->s.next = new_block;
          }
          return current;
      }
      current = current->s.next;
  }
  return NULL;
}

void *malloc(size_t size) {
  pthread_mutex_lock(&lock);
  if (!size) {
    pthread_mutex_unlock(&lock);
    return NULL;
  }
  size_t full_size = size + sizeof(union Header);

  union Header *header = find_free_block(size);
  if (header) {
    header->s.free = 0;
    pthread_mutex_unlock(&lock);
    return (void *)(header + 1);
  }

  union Header *block = sbrk(full_size);
  block->s.size = full_size;
  block->s.free = 0;
  block->s.next = NULL;

  header = block;
  if (!head) {
    head = header;
  }
  if (tail) {
    tail->s.next = header;
  }
  tail = header;

  pthread_mutex_unlock(&lock);
  return (void *)(header + 1);
}

void free(void *ptr) {
  pthread_mutex_lock(&lock);
  if (!ptr) {
    pthread_mutex_unlock(&lock);
    return;
  }

  union Header *header = (union Header *)(ptr - 1);
  void *programbreak = sbrk(0);

  if ((char *)ptr + header->s.size == programbreak) {
    if (head == tail) {
      head = tail = NULL;
    } else {
      union Header *current = head;
      while (current) {
        if (current->s.next == tail) {
          current->s.next = NULL;
          tail = current;
        }
        current = current->s.next;
      }
    }
    sbrk(0 - sizeof(union Header) - header->s.size);
    pthread_mutex_unlock(&lock);
    return;
  }
  pthread_mutex_unlock(&lock);
}

void *realloc(void *ptr, size_t new_size) {
    if (!ptr) {
        return malloc(new_size); 
    }
    if (new_size == 0) {
        free(ptr); 
        return NULL;
    }

    union Header *header = (union Header *)ptr - 1;
    if (header->s.size >= new_size) {
        return ptr; 
    }

    void *new_ptr = malloc(new_size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, header->s.size - sizeof(union Header)); 
        free(ptr);
    }
    return new_ptr;
}

void *calloc(size_t num, size_t size) {
    size_t total_size = num * size;
    void *ptr = malloc(total_size);
    if (ptr) {
        memset(ptr, 0, total_size); 
    }
    return ptr;
}