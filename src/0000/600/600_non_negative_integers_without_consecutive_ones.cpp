// 600_non_negative_integers_without_consecutive_ones
// Nevin Zheng
// 7/25/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// This Solution is right, but TLE
// int find(int max, int sum, int pos, bool prev) {
//  if (sum > max) return 0;       // Exceeded max
//  if (1 << pos > max) return 1;  // sum <= num, and reached bit limit
//  if (prev) return find(max, sum, pos + 1, false);
//  return find(max, sum, pos + 1, false) +
//         find(max, sum + (1 << pos), pos + 1, true);
//}
//
// int findIntegers(int n) { return find(n, 0, 0, false); }

int countIntegers(int sum, int max) {
  if (sum > max) return 0;
  if (sum & 1) {  // Current Int ends in 1
    // get count of appending 0, then add 1 to it, simulating appending 1
    return 1 + countIntegers((sum << 1) | 0, max);
  }
  // Ends with 0
  // Get count of appending a 0, add 1 to it
  // Get count of appending 1
  return 1 + countIntegers((sum << 1) | 0, max) +
         countIntegers((sum << 1) | 1, max);
}

int findIntegers(int n) {
  // Add Extra digit 0/1
  return 1 + countIntegers(1, n);
}

TEST_CASE("600ex1", "[600]") {
  const auto n = 5;
  const auto expected = 5;
  REQUIRE(findIntegers(n) == expected);
}

TEST_CASE("600ex2", "[600]") {
  const auto n = 1;
  const auto expected = 2;
  REQUIRE(findIntegers(n) == expected);
}

TEST_CASE("600ex3", "[600]") {
  const auto n = 2;
  const auto expected = 3;
  REQUIRE(findIntegers(n) == expected);
}
