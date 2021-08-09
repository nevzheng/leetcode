// 415_add_strings
// Nevin Zheng
// 8/9/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static string addStrings(string num1, string num2) {
    string ans;
    constexpr char kBase = static_cast<char>(10);
    auto it = num1.rbegin();
    auto jt = num2.rbegin();
    auto carry = '\0';
    while (it != num1.rend() or jt != num2.rend() or carry > 0) {
      char sum = (it != num1.rend() ? *it - '0' : '\0') +
                 (jt != num2.rend() ? *jt - '0' : '\0') + carry;
      char digit = sum % kBase;
      carry = sum / kBase;
      ans += digit + '0';
      if (it != num1.rend()) ++it;
      if (jt != num2.rend()) ++jt;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};

TEST_CASE("415ex1", "[415]") {
  const auto num1 = "11"s;
  const auto num2 = "123"s;
  const auto expected = "134"s;
  REQUIRE(Solution::addStrings(num1, num2) == expected);
}

TEST_CASE("415ex2", "[415]") {
  const auto num1 = "11"s;
  const auto num2 = "123"s;
  const auto expected = "134"s;
  REQUIRE(Solution::addStrings(num1, num2) == expected);
}

TEST_CASE("415ex3", "[415]") {
  const auto num1 = "0"s;
  const auto num2 = "0"s;
  const auto expected = "0"s;
  REQUIRE(Solution::addStrings(num1, num2) == expected);
}
