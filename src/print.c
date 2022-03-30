#include "print.h"
#include <stddef.h>
#include <stdio.h>
void print_int_int(int a, char const *op, int b) {
  printf("%d %s %d\n", a, op, b);
}
void print_size_t_size_t(size_t a, char const *op, size_t b) {
  printf("%zu %s %zu\n", a, op, b);
}
void print_int_size_t(int a, char const *op, size_t b) {
  printf("%d %s %zu\n", a, op, b);
}
void print_size_t_int(size_t a, char const *op, int b) {
  printf("%zu %s %d\n", a, op, b);
}
void print_double_size_t(double a, char const *op, size_t b) {
  printf("%f %s %zu\n", a, op, b);
}
void print_size_t_double(size_t a, char const *op, double b) {
  printf("%zu %s %f\n", a, op, b);
}
