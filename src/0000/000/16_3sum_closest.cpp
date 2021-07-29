// 16_3sum_closest
// Nevin Zheng
// 7/27/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

int threeSumClosest(vector<int>& A, int tgt) {
  // Sort in n*lgn time, constant space
  sort(begin(A), end(A));
  auto closest = INT_MAX;
  auto diff = INT_MAX;
  auto len = A.size();
  for (auto i = 0UL; i <= len - 3; i++) {
    auto j = i + 1;
    auto k = len - 1;
    while (j < k) {
      auto sum = A[i] + A[j] + A[k];
      if (abs(tgt - sum) < abs(diff)) {
        closest = sum;
        diff = tgt - sum;
      }
      if (sum == tgt) return sum;
      sum < tgt ? j++ : k--;
    }
  }
  return closest;
}

TEST_CASE("16ex1", "[16]") {
  vector<int> nums{-1, 2, 1, -4};
  const auto target = 1;
  const auto expected = 2;
  REQUIRE(threeSumClosest(nums, target) == expected);
}

TEST_CASE("16ex2", "[16]") {
  vector<int> nums{1, 1, 1, 1};
  const auto target = 0;
  const auto expected = 3;
  REQUIRE(threeSumClosest(nums, target) == expected);
}

TEST_CASE("16ex3", "[16]") {
  vector<int> nums{1, 1, 1, 0};
  const auto target = -100;
  const auto expected = 2;
  REQUIRE(threeSumClosest(nums, target) == expected);
}

TEST_CASE("16ex4", "[16]") {
  vector<int> nums{1, 2, 4, 8, 16, 32, 64, 128};
  const auto target = 82;
  const auto expected = 82;
  REQUIRE(threeSumClosest(nums, target) == expected);
}
