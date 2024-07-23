#include "./memalloc.h"
#include "stdlib.h"
#include <unistd.h>

union Header *head = NULL, *tail = NULL;

union Header *find_free_block(size_t bsize) {
  union Header *current = head;
  while (current) {
    if (current->s.free && current->s.size == bsize) {
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
