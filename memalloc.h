#ifndef MEMALLOC_H

#define MEMALLOC_H

#include <stddef.h>

typedef char ALIGN[16];
union Header {
  struct {
    union Header *next;
    size_t size;
    unsigned free;
  } s;
  ALIGN stub;
};
void *malloc(size_t nbytes);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t n, size_t size);
#endif
