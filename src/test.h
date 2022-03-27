/**
 * ATTENTION: Vous n'avez en aucun cas le droit de toucher à ce fichier.
 * Une modification de ce ficher sera sanctionné par une note nulle !
 */
#ifndef TEST_HEADER
#define TEST_HEADER
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
void print_int_int(int a, char const *op, int b);
void print_size_t_size_t(size_t a, char const *op, size_t b);
void print_int_size_t(int a, char const *op, size_t b);
void print_size_t_int(size_t a, char const *op, int b);
void print_int_int(int a, char const *op, int b);
typedef struct TestFunction {
  void (*test)();
  char *name;
} TestFunction;
extern int test_passed;
extern int test_failed;
extern TestFunction unit_test[100];
extern int number_test;
bool run_all_test();
#define COLOR "\033["
#define RED COLOR "31m"
#define GREEN COLOR "32m"
#define DEFAULT COLOR "0m"
#define print(...)                                                             \
  do {                                                                         \
    printf(__VA_ARGS__);                                                       \
    fputs(DEFAULT, stdout);                                                    \
  } while (0)
#define TEST(A) void test##A(const char *test_name)

#define GET_N_ARGS(_1, _2, _3, _4, _5, N, ...) N
#define COUNT_ARGS(...) GET_N_ARGS(__VA_ARGS__, 5, 4, 3, 2, 1)
#define STRINGIFY(A) #A
#define OVERRIDE(_1, _2, _3, _4, N, ...) N
#define REGISTER1(A)                                                           \
  unit_test[number_test++] = (TestFunction) {                                  \
    .test = test##A, .name = STRINGIFY(A)                                      \
  }
#define REGISTER2(A, B)                                                        \
  REGISTER1(A);                                                                \
  REGISTER1(B)
#define REGISTER3(A, B, C)                                                     \
  REGISTER2(A, B);                                                             \
  REGISTER1(C)
#define REGISTER4(A, B, C, D)                                                  \
  REGISTER3(A, B, C);                                                          \
  REGISTER1(D)

#define REGISTER(...)                                                          \
  do {                                                                         \
    OVERRIDE(__VA_ARGS__, REGISTER4, REGISTER3, REGISTER2, REGISTER1)          \
    (__VA_ARGS__);                                                             \
  } while (0)
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
           : _Generic((B), int                                                 \
                      : print_int_int, size_t                                  \
                      : print_int_size_t),                                     \
             size_t                                                            \
           : _Generic((B), size_t                                              \
                      : print_size_t_size_t, int                               \
                      : print_size_t_int))
#define REQUIRE_OP(A, Op, B, ...)                                              \
  _REQUIRE((A Op B), PrintOp(A, B), A, #Op, B, __VA_ARGS__);
#endif
