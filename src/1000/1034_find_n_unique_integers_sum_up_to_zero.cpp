// 1034_find_n_unique_integers_sum_up_to_zero
// Nevin Zheng
// 8/11/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static vector<int> sumZero(int n) {
    vector<int> ans;
    if (n % 2) ans.push_back(0);
    for (auto i = 1; i <= n / 2; ++i) {
      ans.push_back(-i);
      ans.push_back(i);
    }
    return ans;
  }
};

TEST_CASE("1034::1", "[1034]") {
  const auto n = 5;
  auto result = Solution::sumZero(n);
  REQUIRE(std::accumulate(result.begin(), result.end(), 0) == 0);
}

TEST_CASE("1034::2", "[1034]") {
  const auto n = 3;
  auto result = Solution::sumZero(n);
  REQUIRE(std::accumulate(result.begin(), result.end(), 0) == 0);
}

TEST_CASE("1034::3", "[1034]") {
  const auto n = 1;
  auto result = Solution::sumZero(n);
  REQUIRE(std::accumulate(result.begin(), result.end(), 0) == 0);
}

TEST_CASE("1034::4", "[1034]") {
  const auto n = 1000;
  auto result = Solution::sumZero(n);
  REQUIRE(std::accumulate(result.begin(), result.end(), 0) == 0);
}

TEST_CASE("1034::5", "[1034]") {
  const auto n = 999;
  auto result = Solution::sumZero(n);
  REQUIRE(std::accumulate(result.begin(), result.end(), 0) == 0);
}
