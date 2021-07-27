// 1143_longest_common_subsequence
// Nevin Zheng
// 7/26/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

int longestCommonSubsequence(const string& X, const string& Y) {
  auto x_len = X.size();
  auto y_len = Y.size();
  vector<vector<int>> dp(x_len + 1, vector(y_len + 1, 0));
  for (auto i = 1UL; i <= x_len; i++) {
    for (auto j = 1UL; j <= y_len; j++) {
      if (X[i - 1] == Y[j - 1])
        dp[i][j] = 1 + dp[i - 1][j - 1];
      else
        dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
    }
  }
  return dp.back().back();
}

TEST_CASE("1143ex1", "[1143]") {
  auto X = "abcde";
  auto Y = "ace";
  auto expected = 3;
  REQUIRE(longestCommonSubsequence(X, Y) == expected);
}

TEST_CASE("1143ex2", "[1143]") {
  auto X = "abc";
  auto Y = "abc";
  auto expected = 3;
  REQUIRE(longestCommonSubsequence(X, Y) == expected);
}