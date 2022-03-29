#pragma once
#include <stdlib.h>
extern int nb_malloc;
extern int nb_free;
struct Pointer {
  size_t allocated;
  void *ptr;
};
struct PointersStore {
  int index_max;
  struct Pointer pointers[100];
  size_t bytes_allocated;
};
extern struct PointersStore pointers_store;

#ifdef __GNUC__

extern void *__libc_malloc(size_t size);
extern void __libc_free(void *ptr);

#endif
