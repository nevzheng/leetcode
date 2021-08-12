// OA_24_substr_of_size_k_with_k_distinct_char
// Nevin Zheng
// 8/11/21
// https://leetcode.com/discuss/interview-question/370112

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static vector<string> uniqueKSubstr(const string& s, int k) {
    set<string> ans;
    auto l = 0;
    auto r = 0;
    map<char, int> count;
    while (r < static_cast<int>(s.size())) {
      ++count[s[r]];                             // Grow window
      while (count[s[r]] != 1) --count[s[l++]];  // Shrink/resolve conflict
      if (r - l + 1 == k) {
        ans.insert(s.substr(l, k));  // add to set
        --count[s[l++]];             // continue search
      }
      ++r;
    }
    return vector(ans.begin(), ans.end());
  }
};

TEST_CASE("OA::24::1", "[oa24]") {
  const string s = "abcabc";
  const int k = 3;
  vector<string> expected{"abc", "bca", "cab"};
  auto res = Solution::uniqueKSubstr(s, k);
  std::sort(res.begin(), res.end());
  std::sort(expected.begin(), expected.end());
  REQUIRE(res == expected);
}

TEST_CASE("OA::24::2", "[oa24]") {
  const string s = "abacab";
  const int k = 3;
  vector<string> expected{"bac", "cab"};
  auto res = Solution::uniqueKSubstr(s, k);
  std::sort(res.begin(), res.end());
  std::sort(expected.begin(), expected.end());
  REQUIRE(res == expected);
}

TEST_CASE("OA::24::3", "[oa24]") {
  const string s = "awaglknagawunagwkwagl";
  const int k = 4;
  vector<string> expected{"wagl", "aglk", "glkn", "lkna", "knag", "gawu",
                          "awun", "wuna", "unag", "nagw", "agwk", "kwag"};
  auto res = Solution::uniqueKSubstr(s, k);
  std::sort(res.begin(), res.end());
  std::sort(expected.begin(), expected.end());
  REQUIRE(res == expected);
}