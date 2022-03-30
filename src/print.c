#include "print.h"
#include <stddef.h>
#include <stdio.h>
void print_intint(int a, char const *op, int b) {
  printf("%d %s %d\n", a, op, b);
}
void print_size_tsize_t(size_t a, char const *op, size_t b) {
  printf("%zu %s %zu\n", a, op, b);
}
void print_intsize_t(int a, char const *op, size_t b) {
  printf("%d %s %zu\n", a, op, b);
}
void print_size_tint(size_t a, char const *op, int b) {
  printf("%zu %s %d\n", a, op, b);
}
void print_doublesize_t(double a, char const *op, size_t b) {
  printf("%f %s %zu\n", a, op, b);
}
void print_size_tdouble(size_t a, char const *op, double b) {
  printf("%zu %s %f\n", a, op, b);
}
void print_intdouble(int a, char const *op, double b) {
  printf("%d %s %f\n", a, op, b);
}
void print_doubleint(double a, char const *op, int b) {
  printf("%f %s %d\n", a, op, b);
}
void print_doubledouble(double a, char const *op, double b) {
  printf("%f %s %f\n", a, op, b);
}
