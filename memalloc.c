#include "./memalloc.h"
#include "stdlib.h"
#include <unistd.h>

union Header *head = NULL, *tail = NULL;

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
  if (!size) {
    return NULL;
  }
  size_t full_size = size + sizeof(union Header);

  union Header *header = find_free_block(size);
  if (header) {
    header->s.free = 0;
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

  return (void *)(header + 1);
}

void free(void *ptr) {
  if (!ptr) {
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
    return;
  }
}
