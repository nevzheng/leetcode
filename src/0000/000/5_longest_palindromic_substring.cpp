// 5_longest_palindromic_substring
// Nevin Zheng
// 8/15/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * In this approach we iterate over each char of the string, treating it as
 * a center of a palindrome. For each center, we try to grow the left and
 * right bounds by comparing s[l]==s[r] incrementing size and bounds if the
 * palindrome property is maintained.
 * There are palindromes with even and odd parity which means that we chose
 * (i, i), and (i,i+1) as centers for each palindrome.
 * There are O(2*n) centers and the expansion takes O(n) time.
 * Time: O(n^2)
 * Space: O(1)
 */
class Solution {
 public:
  static int expand(const string& s, int l, int r) {
    // Expand Bounds
    while (0 <= l && r < static_cast<int>(s.size()) && s[l] == s[r]) --l, ++r;
    return r - l - 1;  // Return len, MINUS 1 not PLUS 1.
  }

  static string longestPalindrome(const string& s) {
    if (s.empty()) return "";
    auto l = 0;
    auto max_len = 0;
    for (auto i = 0; i < static_cast<int>(s.size()); ++i) {
      auto odd = expand(s, i, i);
      auto even = expand(s, i, i + 1);
      auto len = max(odd, even);
      if (len > max_len) {
        max_len = len;
        l = i - (len - 1) / 2;
      }
    }
    return s.substr(l, max_len);
  }
};

TEST_CASE("5::1", "[5]") {
  const auto s = "babac"s;
  const auto expected = "bab"s;
  REQUIRE(Solution::longestPalindrome(s) == expected);
}

TEST_CASE("5::2", "[5]") {
  const auto s = "cbbd"s;
  const auto expected = "bb"s;
  REQUIRE(Solution::longestPalindrome(s) == expected);
}

TEST_CASE("5::3", "[5]") {
  const auto s = "a"s;
  const auto expected = "a"s;
  REQUIRE(Solution::longestPalindrome(s) == expected);
}

TEST_CASE("5::4", "[5]") {
  const auto s = "ac"s;
  const auto expected = "a"s;
  REQUIRE(Solution::longestPalindrome(s) == expected);
}

TEST_CASE("5::5", "[5]") {
  const auto s = "aacabdkacaa"s;
  const auto expected = "aca"s;
  REQUIRE(Solution::longestPalindrome(s) == expected);
}
