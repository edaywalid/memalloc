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

#endif
