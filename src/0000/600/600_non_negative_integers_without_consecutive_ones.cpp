// 600_non_negative_integers_without_consecutive_ones
// Nevin Zheng
// 7/25/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;
using Cache = map<pair<uint32_t, uint32_t>, int>;

int countIntegers(Cache& cache, uint32_t max, uint32_t n_bits, uint32_t sum,
                  uint32_t digit) {
  if (cache.count({n_bits, digit}) != 0U) return cache.at({n_bits, digit});
  // Reached Depth limit
  if (n_bits == 0 and sum > max) return 0;   // Invalid String
  if (n_bits == 0 and sum <= max) return 1;  // Valid String
  sum <<= 1;                                 // Make Room for the new digit
  if (digit == 0) {  // Place 0, Next Digit can be 0 or 1;
    auto x = countIntegers(cache, max, n_bits - 1, sum, 0) +
             countIntegers(cache, max, n_bits - 1, sum, 1);
    return cache[{n_bits, digit}] = x;
  }
  if (digit == 1) {  // If we place a 1, next digit must be 0;
    auto x = countIntegers(cache, max, n_bits - 1, sum + 1, 0);
    return cache[{n_bits, digit}] = x;
  }
  return 0;  // Unreachable
}

int findIntegers(int n) {
  int n_bits = ceil(log2(n));  // Number of bits to place
  Cache cache;
  return countIntegers(cache, n, n_bits, 0, 0) +
         countIntegers(cache, n, n_bits, 0, 1);
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
