// 62_unique_paths
// Nevin Zheng
// 8/15/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * This is a straightforward DP problem.
 * We let dp[i][j] = number of paths to get to j
 * dp[0][0] =1
 * dp[0][j] = dp[0][j-1] // First Row
 * dp[i][0] = dp[i-1][0] // First Col
 * dp[i][j] = dp[i-1][j] + dp[i][j-1]
 * The naive solution will use O(MN) time and space.
 * Space can be optimized further, but is unnecessary for the given constrains
 */
class Solution {
 public:
  static int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector(n, 0));
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        if (i == 0 and j == 0) {
          dp[i][j] = 1;
        } else if (i == 0) {
          dp[i][j] = dp[0][j - 1];
        } else if (j == 0) {
          dp[i][j] = dp[i - 1][j];
        } else {
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
      }
    }
    return dp.back().back();
  }
};

TEST_CASE("62::1", "[62]") {
  const auto m = 3;
  const auto n = 7;
  const auto expected = 28;
  REQUIRE(Solution::uniquePaths(m, n) == expected);
}

TEST_CASE("62::2", "[62]") {
  const auto m = 3;
  const auto n = 2;
  const auto expected = 3;
  REQUIRE(Solution::uniquePaths(m, n) == expected);
}

TEST_CASE("62::4", "[62]") {
  const auto m = 7;
  const auto n = 3;
  const auto expected = 28;
  REQUIRE(Solution::uniquePaths(m, n) == expected);
}

TEST_CASE("62::5", "[62]") {
  const auto m = 3;
  const auto n = 3;
  const auto expected = 6;
  REQUIRE(Solution::uniquePaths(m, n) == expected);
}
