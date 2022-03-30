/**
 * ATTENTION: Vous n'avez en aucun cas le droit de toucher à ce fichier.
 * Une modification de ce ficher sera sanctionné par une note nulle !
 */
#ifndef TEST_HEADER
#define TEST_HEADER
#include "tuc/print.h"
#include "tuc/tuc_export.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
typedef struct TestFunction {
  void (*test)();
  char *name;
} TestFunction;
TUC_EXPORT extern int test_passed;
TUC_EXPORT extern int test_failed;
TUC_EXPORT extern TestFunction unit_test[100];
TUC_EXPORT extern int number_test;
TUC_EXPORT bool run_all_tests();
#ifdef __GNUC__
#define CTOR __attribute__((constructor))
#else
#define CTOR
#endif
#define TEST(A)                                                                \
  void test##A(const char *test_name);                                         \
  CTOR void register_##A() {                                                   \
    unit_test[number_test++] =                                                 \
        (TestFunction){.test = test##A, .name = STRINGIFY(A)};                 \
  }                                                                            \
  void test##A(const char *test_name)

#define STRINGIFY(A) #A
#define REGISTER(A)                                                            \
  unit_test[number_test++] = (TestFunction) {                                  \
    .test = test##A, .name = STRINGIFY(A)                                      \
  }
static inline void dummy_print(int a, char const *b, int c) {
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
