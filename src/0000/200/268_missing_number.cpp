// 268_missing_number
// Nevin Zheng
// 7/26/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

int missingNumber(const vector<int>& nums) {
  auto n = nums.size();
  auto total = (n) * (n + 1UL) / 2UL;
  return total - std::accumulate(begin(nums), end(nums), 0UL);
}

TEST_CASE("268ex1", "[268]") {
  const vector<int> input = {3, 0, 1};
  const auto expected = 2;
  REQUIRE(missingNumber(input) == expected);
}

TEST_CASE("268ex2", "[268]") {
  auto input = {0, 1};
  auto expected = 2;
  REQUIRE(missingNumber(input) == expected);
}

TEST_CASE("268ex3", "[268]") {
  auto input = {9, 6, 4, 2, 3, 5, 7, 0, 1};
  auto expected = 8;
  REQUIRE(missingNumber(input) == expected);
}

TEST_CASE("268ex4", "[268]") {
  auto input = {0};
  auto expected = 1;
  REQUIRE(missingNumber(input) == expected);
}