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
TUC_EXPORT void print_int_int(int a, char const *op, int b);
TUC_EXPORT void print_size_t_size_t(size_t a, char const *op, size_t b);
TUC_EXPORT void print_int_size_t(int a, char const *op, size_t b);
TUC_EXPORT void print_size_t_int(size_t a, char const *op, int b);
