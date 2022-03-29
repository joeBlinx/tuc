#include "allocator.h"
int nb_malloc = 0;
int nb_free = 0;
struct PointersStore pointers_store = {.index_max = 0, .bytes_allocated = 0};
#ifdef __GNUC__
#include <stdbool.h>
#include <stdio.h>
static bool use_custom = true;
static void add_new_pointer(void *ptr, size_t bytes) {
  pointers_store.bytes_allocated += bytes;
  pointers_store.pointers[pointers_store.index_max++] =
      (struct Pointer){.allocated = bytes, .ptr = ptr};
}
static void remove_pointer(void *ptr) {
  int index = 0;
  while (index < pointers_store.index_max &&
         ptr != pointers_store.pointers[index].ptr) {
    index++;
  }
  if (index == pointers_store.index_max) {
    return;
  }
  pointers_store.bytes_allocated -= pointers_store.pointers[index].allocated;
  for (int i = index; i < pointers_store.index_max; i++) {
    pointers_store.pointers[i] = pointers_store.pointers[i + 1];
  }
}
void *my_malloc(size_t bytes) {
  static bool first_time = true;
  if (first_time) {
    use_custom = false;
    puts("Beginning of Test");
    use_custom = true;
    first_time = false;
  }
  void *ptr = __libc_malloc(bytes);
  add_new_pointer(ptr, bytes);
  nb_malloc += 1;
  return ptr;
}
void *malloc(size_t bytes) {
  if (use_custom) {
    return my_malloc(bytes);
  }
  return __libc_malloc(bytes);
}
void free(void *ptr) {
  remove_pointer(ptr);
  nb_free += 1;
  __libc_free(ptr);
}
#endif
