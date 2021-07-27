// 516_longest_palindromic_subsequence
// Nevin Zheng
// 7/26/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

int longestCommonSubsequence(const string& X, const string& Y) {
  auto x_len = X.length();
  auto y_len = Y.length();
  vector<vector<int>> dp(x_len + 1, vector(y_len + 1, 0));
  for (auto x = 1UL; x <= x_len; x++) {
    for (auto y = 1UL; y <= y_len; y++) {
      if (X[x - 1] == Y[y - 1])
        dp[x][y] = 1 + dp[x - 1][y - 1];
      else
        dp[x][y] = max(dp[x - 1][y], dp[x][y - 1]);
    }
  }
  return dp.back().back();
}

int longestPalindromeSubseq(const string& x) {
  auto y = x;
  reverse(begin(y), end(y));
  return longestCommonSubsequence(x, y);
}

TEST_CASE("516ex1", "[516]") {
  const auto s = "bbbab";
  const auto expected = 4;
  REQUIRE(longestPalindromeSubseq(s) == expected);
}

TEST_CASE("516ex2", "[516]") {
  const auto s = "cbbd";
  const auto expected = 2;
  REQUIRE(longestPalindromeSubseq(s) == expected);
}
