// 837_new_21_game
// Nevin Zheng
// 8/5/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * In This solution we write a recursive definition
 * for the probability P(i) which is the probability of seeing the sum i
 * P(n) = Sum(P(n-i)P(i)) for all i in [1,W]
 * P(0) = 1
 * P( n < 0 ) = 0;
 * P( n > k) = 0; as w stop drawing cards
 * P(i) in [1,W] is the probability of drawing a card, => 1/W
 * The naive implementation below runs in O(n*W) time and O(n) space
 */
class Solution {
 public:
  static double new21Game(int n, int k, int W) {
    // dp[i] = probability of sum i
    // We're only interested up to the nth sum
    vector dp(n + 1, 0.);
    dp[0] = 1;  // 100% chance 0 is encountered

    for (auto i = 1; i <= n; i++) {  // Iterate over all sums from 1 to n
      for (auto j = 1; j <= W; ++j) {
        auto idx = i - j;
        if (0 <= idx and idx < k) dp[i] += dp[idx] / W;
      }
    }

    return std::accumulate(dp.begin() + k, dp.begin() + (n + 1), 0.);
  }
};

static constexpr auto kEpsilon = 10e-5;

TEST_CASE("837ex1", "[837]") {
  const auto n = 10;
  const auto k = 1;
  const auto max_points = 10;
  const auto expected = 1.0;
  auto delta = abs(Solution::new21Game(n, k, max_points) - expected);
  REQUIRE(delta <= kEpsilon);
}

TEST_CASE("837ex2", "[837]") {
  const auto n = 6;
  const auto k = 1;
  const auto max_points = 10;
  const auto expected = 0.6;
  auto delta = abs(Solution::new21Game(n, k, max_points) - expected);
  REQUIRE(delta <= kEpsilon);
}

TEST_CASE("837ex3", "[837]") {
  const auto n = 21;
  const auto k = 17;
  const auto max_points = 10;
  const auto expected = 0.73278;
  auto delta = abs(Solution::new21Game(n, k, max_points) - expected);
  REQUIRE(delta <= kEpsilon);
}