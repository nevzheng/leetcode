// 633_sum_of_squares
// Nevin Zheng
// 8/25/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * This statement is based on fermat's theorem:
 * "Any positive number n is expressible as a sum of two squares iff in the
 * prime factorization of n, every prime factor of the form 4k+3 occurs an
 * even number of times
 */
class Solution {
 public:
  static bool judgeSquareSum(int n) {
    for (auto c = 2; c <= n; ++c) {
      if (n % c == 0) {  // Is divisible by c
        auto count = 0;
        while (n % c == 0) {  // Count how many times factor occurs
          ++count;
          n /= c;
        }
        // If the factor is of form 4k+3 and occurs an odd number of times
        // Then it's not a sum of squares
        if (c % 4 == 3 && count % 2 != 0) return false;
      }
    }
    return true;
  }
};

TEST_CASE("633::1", "[633]") {
  const auto c = 5;
  const auto expected = true;
  REQUIRE(Solution::judgeSquareSum(c) == expected);
}

TEST_CASE("633::2", "[633]") {
  const auto c = 3;
  const auto expected = false;
  REQUIRE(Solution::judgeSquareSum(c) == expected);
}

TEST_CASE("633::3", "[633]") {
  const auto c = 4;
  const auto expected = true;
  REQUIRE(Solution::judgeSquareSum(c) == expected);
}

TEST_CASE("633::4", "[633]") {
  const auto c = 2;
  const auto expected = true;
  REQUIRE(Solution::judgeSquareSum(c) == expected);
}

TEST_CASE("633::5", "[633]") {
  const auto c = 1;
  const auto expected = true;
  REQUIRE(Solution::judgeSquareSum(c) == expected);
}
