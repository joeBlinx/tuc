#pragma once
#include "tuc/tuc_export.h"
#include <stddef.h>
#define COLOR "\033["
#define RED COLOR "31m"
#define GREEN COLOR "32m"
#define DEFAULT COLOR "0m"
#define print(...)                                                             \
  do {                                                                         \
    printf(__VA_ARGS__);                                                       \
    fputs(DEFAULT, stdout);                                                    \
  } while (0)
TUC_EXPORT void print_intint(int a, char const* op, int b);
TUC_EXPORT void print_intsize_t(int a, char const* op, size_t b);
TUC_EXPORT void print_intdouble(int a, char const* op, double b);
TUC_EXPORT void print_size_tsize_t(size_t a, char const* op, size_t b);
TUC_EXPORT void print_size_tint(size_t a, char const* op, int b);
TUC_EXPORT void print_size_tdouble(size_t a, char const* op, double b);
TUC_EXPORT void print_doublesize_t(double a, char const* op, size_t b);
TUC_EXPORT void print_doubleint(double a, char const* op, int b);
TUC_EXPORT void print_doubledouble(double a, char const* op, double b);

#define GET_N_ARGS(_1, _2, _3, _4, _5, N, ...) N
#define COUNT_ARGS(...) GET_N_ARGS(__VA_ARGS__, 5, 4, 3, 2, 1)
#define OVERRIDE(_1, _2, _3, _4, N, ...) N
#define GENERIC1(type1, type2)                                                 \
  type2: print_##type1##type2)

#define GENERIC2(type1, type2, type3)                                          \
  type2:                                                                       \
  print_##type1##type2, GENERIC1(type1, type3)

#define GENERIC3(type1, type2, type3, type4)                                   \
  type2:                                                                       \
  print_##type1##type2, GENERIC2(type1, type3, type4)

#define GENERIC4(type1, type2, type3, type4, type5)                            \
  type2:                                                                       \
  print_##type1##type2, GENERIC2(type1, type3, type4, type5)

#define GENERIC(type_to_test, type, ...)                                       \
        _Generic((type_to_test), \
    OVERRIDE(__VA_ARGS__, GENERIC4, GENERIC3, GENERIC2, GENERIC1)          \
    (type, __VA_ARGS__)
