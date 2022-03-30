#include "tuc/tuc.h"
TEST(FirstTU) {
  int a = 1;
  int b = 2;
  REQUIRE_OP(a, !=, b);
}
int main(void) {
  REGISTER(FirstTU);
  return run_all_tests();
}
