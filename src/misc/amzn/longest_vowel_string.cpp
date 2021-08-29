// longest_vowel_string
// Nevin Zheng
// 8/29/21
// https://leetcode.com/discuss/interview-question/233724/Amazon-online-assessment-Longest-string-made-up-of-only-vowels
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int longestVowelString(const string& s) {
    auto is_vowel = [](auto c) {
      return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };
    int len = static_cast<int>(s.size());
    int l = 0;
    int r = len - 1;
    while (l < len && is_vowel(s[l])) ++l;
    while (r >= 0 && is_vowel(s[r])) --r;
    if (l > r) return len;           // All Vowels
    auto res = l + ((len - 1) - r);  // Len of left and right vowel runs
    // Find the longest substring that is only vowels
    auto longest = 0;
    auto cur = 0;
    for (auto i = l + 1; i < r; ++i) {
      cur = is_vowel(s[i]) ? cur + 1 : 0;
      longest = max(longest, cur);
    }
    return longest + res;
  }
};

TEST_CASE("longest_vowel_string::1", "[]") {
  auto s = "earthproblem"s;
  auto expected = 3;
  REQUIRE(Solution::longestVowelString(s) == expected);
}

TEST_CASE("longest_vowel_string::2", "[]") {
  auto s = "letsgosomewhere"s;
  auto expected = 2;
  REQUIRE(Solution::longestVowelString(s) == expected);
}
