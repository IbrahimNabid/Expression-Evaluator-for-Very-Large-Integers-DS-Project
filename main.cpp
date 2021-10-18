#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "BigInt.h"
#include <cstdlib>
#include <doctest.h>
#include <sstream> 

TEST_CASE("BigInt") {

  ds::BigInt a("456");
  ds::BigInt b("11239");

  SUBCASE("Addition") {
    ds::BigInt r = a + b;
    std::stringstream ss;
    ss << r;
    CHECK(ss.str() == "11695");
  }


  SUBCASE("Subtraction") {
    ds::BigInt r = a - b;
    std::stringstream ss;
    ss << r;
    CHECK(ss.str() == "10783");
  }
}
