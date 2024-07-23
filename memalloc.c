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

