#include "tuc/tuc.h"

void print_int_int(int a, char const *op, int b) {
  printf("%d %s %d\n", a, op, b);
}
void print_size_t_size_t(size_t a, char const *op, size_t b) {
  printf("%ld %s %ld\n", a, op, b);
}
void print_int_size_t(int a, char const *op, size_t b) {
  printf("%d %s %ld\n", a, op, b);
}
void print_size_t_int(size_t a, char const *op, int b) {
  printf("%ld %s %d\n", a, op, b);
}
struct Pointer {
  size_t allocated;
  void *ptr;
};
struct PointersStore {
  int index_max;
  struct Pointer pointers[100];
  size_t bytes_allocated;
};
static struct PointersStore pointers_store = {.index_max = 0,
                                              .bytes_allocated = 0};
int test_passed = 0;
int test_failed = 0;
static int nb_malloc = 0;
static int nb_free = 0;
TestFunction unit_test[100] = {0};
int number_test = 0;
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
#ifdef __GNUC__
static bool use_custom = true;
extern void *__libc_malloc(size_t size);
extern void __libc_free(void *ptr);
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
TEST(MemCheck) {
  REQUIRE_OP(nb_malloc, ==, nb_free, "Nb Free %d, Nb Malloc %d\n", nb_free, nb_malloc);
  REQUIRE_OP(pointers_store.bytes_allocated, ==, 0,"Memory not freed %ld\n", pointers_store.bytes_allocated);
}

bool run_all_test() {
  free(malloc(1)); // here to force the alloc of stdout buffer, thus it will not count in nb_alloc and nb_free
  REGISTER(MemCheck);
  for (int test = 0; test < number_test; test++) {
    int failed = test_failed;
    unit_test[test].test(unit_test[test].name);
    if (failed == test_failed) {
      test_passed += 1;
    } else {
    }
  }
  print("==========SUMMARY===========\n");
  printf("Test Launched %d\n", number_test);
  print(GREEN "Test Succeeded %d\n", test_passed);
  print(RED "Test Failed %d\n", test_failed);
  return test_failed;
}
