#ifndef TEST_HEADER
#define TEST_HEADER
#include "tuc/print.h"
#include "tuc/tuc_export.h"
#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
typedef struct TestFunction {
  void (*test)();
  char* name;
} TestFunction;
TUC_EXPORT extern int test_passed;
TUC_EXPORT extern int test_failed;
TUC_EXPORT extern TestFunction unit_test[100];
TUC_EXPORT extern int number_test;
TUC_EXPORT bool run_all_tests();
TUC_EXPORT bool launch_one_test(char const* test);
#ifdef __GNUC__
#define CTOR __attribute__((constructor))
#else
#define CTOR
#endif
#define TEST(A)                                                                \
  void test##A(const char* test_name);                                         \
  CTOR void register_##A() {                                                   \
    unit_test[number_test++] =                                                 \
        (TestFunction){.test = test##A, .name = STRINGIFY(A)};                 \
  }                                                                            \
  void test##A(const char* test_name)

#define STRINGIFY(A) #A
#define REGISTER(A)                                                            \
  unit_test[number_test++] = (TestFunction) {                                  \
    .test = test##A, .name = STRINGIFY(A)                                      \
  }
static inline void dummy_print(int a, char const* b, int c) {
  (void)a;
  (void)b;
  (void)c;
}

#define _REQUIRE(COND, PrintFunction, A, Op, B, ...)                           \
  do {                                                                         \
    if (!(COND)) {                                                             \
      print(RED "===== Test %s failed =====\n", test_name);                    \
      printf("condition " RED #COND DEFAULT " not passed, %s:%d\n", __FILE__,  \
             __LINE__);                                                        \
      if (strcmp(Op, "")) {                                                    \
        PrintFunction(A, Op, B);                                               \
      }                                                                        \
      print(""__VA_ARGS__);                                                    \
      puts("==========================================");                      \
      test_failed += 1;                                                        \
      return;                                                                  \
    }                                                                          \
  } while (0)
#define REQUIRE(COND, ...) _REQUIRE(COND, dummy_print, 0, "", 0, __VA_ARGS__)
#define PrintOp(A, B)                                                          \
  _Generic((A), int                                                            \
           : GENERIC((B), int, int, size_t, double), size_t                    \
           : GENERIC((B), size_t, size_t, int, double), double                 \
           : GENERIC((B), double, size_t, int, double))
#define REQUIRE_OP(A, Op, B, ...)                                              \
  _REQUIRE((A Op B), PrintOp(A, B), A, #Op, B, __VA_ARGS__);
#endif
static inline int parse_opt(int key, char* arg, struct argp_state* state) {
  switch (key) {
  case 'f':
    launch_one_test(arg);
    break;
  }
  return 0;
}
#define RUN_ALL_TESTS(argc, argv)                                              \
  struct argp_option options[] = {                                             \
      {"tuc-filter", 'f', "TEST NAME", 0, "Run only the test TEST NAME"},      \
      {0}};                                                                    \
  struct argp argp = {options, parse_opt, 0, 0};                               \
  if (argc <= 1) {                                                             \
    return run_all_tests();                                                    \
  }                                                                            \
  return argp_parse(&argp, argc, argv, 0, 0, 0);
