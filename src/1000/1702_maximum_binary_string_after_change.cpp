// 1702_maximum_binary_string_after_change
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * After Some experimentation we find that Rule 1 is able to rearrange a string
 * of n Zeros into n-1 ones followed by a 0.
 * We also discover that rule two is able to move all ones in a string to the
 * end of the string. Exposing All Zeros at the front, which we can
 * then apply rule 1 to.
 * Our First step is to keep any leading ones. We want to find the location
 * of the first zero.
 * We can then count the number of zeros and ones, then apply the net result of
 * rule two to the remaining part of the string.
 * We then apply the aggregate rule one to the remaining partition
 * leaving the max number
 * We can also combine rules one and two together to get:
 * Partition zeros in front, ones in back. transform all but the last zero to 1
 */
class Solution {
 public:
  static string maximumBinaryString(string& s) {
    auto l = 0UL;
    // Keep All Leading Ones
    while (l < s.size() && s[l] == '1') ++l;
    auto zeros = 0;
    for (auto i = l; i < s.size(); ++i) {
      zeros += (s[i] == '0') ? 1 : 0;
    }
    for (auto i = l; i < s.size(); ++i) {
      if (zeros >= 1) {
        s[i] = zeros > 1 ? '1' : '0';
        --zeros;
      } else {
        s[i] = '1';
      }
    }
    return s;
  }
};

TEST_CASE("1702::1", "[1702]") {
  auto binary = "000110"s;
  const auto expected = "111011"s;
  REQUIRE(Solution::maximumBinaryString(binary) == expected);
}

TEST_CASE("1702::2", "[1702]") {
  auto binary = "01"s;
  const auto expected = "01"s;
  REQUIRE(Solution::maximumBinaryString(binary) == expected);
}
