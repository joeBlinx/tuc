#include "tuc/tuc.h"
TEST(PrintFunctionGeneric) {
  REQUIRE_OP(1, ==, 1);     // int int
  REQUIRE_OP(1, ==, 1.);    // int double
  REQUIRE_OP(1, ==, 1lu);   // int size_t
  REQUIRE_OP(1., ==, 1);    // double int
  REQUIRE_OP(1., ==, 1.);   // double double
  REQUIRE_OP(1., ==, 1lu);  // double size_t
  REQUIRE_OP(1lu, ==, 1);   // size_t int
  REQUIRE_OP(1lu, ==, 1lu); // size_t size_t
  REQUIRE_OP(1lu, ==, 1.);  // size_t double
}
TEST(LaunchOneTest) {
  REQUIRE_OP(!launch_one_test("PrintFunctionGeneric"), ==, 0);
}
int main(int argc, char** argv) { RUN_ALL_TESTS(argc, argv); }
