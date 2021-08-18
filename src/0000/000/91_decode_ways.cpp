// 91_decode_ways
// Nevin Zheng
// 8/18/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int numDecodings(const string& s) {
    if (s.empty() || s.front() == '0') return 0;
    vector<int> dp(s.size() + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (auto i = 1UL; i < s.size(); ++i) {
      if (s[i] != '0') dp[i + 1] += dp[i];  // Valid Single Digit
      if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6')) {
        dp[i + 1] += dp[i - 1];
      }
    }
    return dp.back();
  }
};

TEST_CASE("91::1", "[91]") {
  string s = "12";
  auto expected = 2;
  REQUIRE(Solution::numDecodings(s) == expected);
}

TEST_CASE("91::2", "[91]") {
  string s = "226";
  auto expected = 3;
  REQUIRE(Solution::numDecodings(s) == expected);
}

TEST_CASE("91::3", "[91]") {
  string s = "0";
  auto expected = 0;
  REQUIRE(Solution::numDecodings(s) == expected);
}

TEST_CASE("91::4", "[91]") {
  string s = "06";
  auto expected = 0;
  REQUIRE(Solution::numDecodings(s) == expected);
}
