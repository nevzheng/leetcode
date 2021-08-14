// 3_longest_substring_without_repeating_chars
// Nevin Zheng
// 8/12/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
using namespace std;

// We Apply a sliding window approach with a set to maintain
// unique substrs. we then keep track of the longest unique substr
// we have seen so far.
// O(N) time and memory;
static const int kAsciiSize = 128;
class Solution {
 public:
  static int lengthOfLongestSubstring(const string& s) {
    vector<char> count(kAsciiSize);
    int l = 0;
    int r = 0;
    int mx = 0;
    while (l <= r and r < static_cast<int>(s.size())) {
      ++count[s[r]];                             // Add a New Char
      while (count[s[r]] != 1) --count[s[l++]];  // Resolve Conflicts
      mx = max(mx, r - l + 1);                   // Take the max size
      ++r;                                       // Increment r
    }
    return mx;
  }
};

TEST_CASE("3::1", "[3]") {
  auto s = "abcabcbb"s;
  auto expected = 3;
  REQUIRE(Solution::lengthOfLongestSubstring(s) == expected);
}

TEST_CASE("3::2", "[3]") {
  auto s = "bbbbb"s;
  auto expected = 1;
  REQUIRE(Solution::lengthOfLongestSubstring(s) == expected);
}

TEST_CASE("3::3", "[3]") {
  auto s = "pwwkew"s;
  auto expected = 3;
  REQUIRE(Solution::lengthOfLongestSubstring(s) == expected);
}

TEST_CASE("3::4", "[3]") {
  auto s = ""s;
  auto expected = 0;
  REQUIRE(Solution::lengthOfLongestSubstring(s) == expected);
}