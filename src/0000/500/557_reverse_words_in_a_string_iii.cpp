// 557_reverse_words_in_a_string_iii
// Nevin Zheng
// 8/31/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static string reverseWords(const string& s) {
    std::stringstream ss(s);
    std::string tok;
    string ans;
    bool first = true;
    while (ss >> tok) {
      std::reverse(tok.begin(), tok.end());
      if (!first) {
        ans += " ";
      } else {
        first = false;
      }
      ans += tok;
    }
    return ans;
  }
};

TEST_CASE("557::1", "[557]") {
  const auto s = "Let's take LeetCode contest"s;
  const auto expected = "s'teL ekat edoCteeL tsetnoc"s;
  REQUIRE(Solution::reverseWords(s) == expected);
}