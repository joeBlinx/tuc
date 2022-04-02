#include "tuc/tuc.h"
#include "tuc/allocator.h"
enum { UNIT_TEST_SIZE = 100 };
int test_passed = 0;
int test_failed = 0;
TestFunction unit_test[UNIT_TEST_SIZE] = {0};
int number_test = 0;
void testMemCheck(const char* test_name) {
  REQUIRE_OP(nb_malloc, ==, nb_free, "Nb Free %d, Nb Malloc %d\n", nb_free,
             nb_malloc);
  REQUIRE_OP(pointers_store.bytes_allocated, ==, 0, "Memory not freed %ld\n",
             pointers_store.bytes_allocated);
}
static TestFunction find_test(char const* test_name) {
  for (int i = 0; i < UNIT_TEST_SIZE; i += 1) {
    if (!strcmp(unit_test[i].name, test_name)) {
      return unit_test[i];
    }
  }
  return (TestFunction){.name = "", .test = NULL};
}
bool launch_one_test(char const* test_name) {
  TestFunction test = find_test(test_name);
  if (!test.test) {
    return false;
  }
  int failed = test_failed;
  print("Launch test: %s\n", test_name);
  test.test(test_name);
  return failed == test_failed;
}
bool run_all_tests() {
  free(malloc(1)); // here to force the alloc of stdout buffer, thus it will
                   // not count in nb_alloc and nb_free
  REGISTER(MemCheck);
  for (int test = 0; test < number_test; test++) {
    int failed = test_failed;
    print("Launch test: %s\n", unit_test[test].name);
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
