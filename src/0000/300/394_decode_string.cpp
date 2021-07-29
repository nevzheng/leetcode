// 394_decode_string
// Nevin Zheng
// 7/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  string decodeString(string s) {
    stack<string> stk;
    for (auto x : s) {
      if (x != ']') {  // Push all character except ]
        stk.push({x});
      } else {
        string tok;
        while (!stk.empty() and stk.top() != "[") {
          tok += stk.top();
          stk.pop();
        }
        stk.pop();  // pop left bracket
        string count_str;
        while (!stk.empty() and isdigit(stk.top().at(0))) {
          count_str += stk.top();
          stk.pop();
        }
        // Reverse and parse the number
        reverse(begin(count_str), end(count_str));
        auto count = count_str.empty() ? 0 : stoi(count_str);
        while (count--) stk.push(tok);
      }
    }
    string ans;
    while (!stk.empty()) {
      ans += stk.top();
      stk.pop();
    }
    reverse(begin(ans), end(ans));
    return ans;
  }
};

TEST_CASE("394ex1", "[394]") {
  const auto s = "3[a]2[bc]"s;
  const auto expected = "aaabcbc"s;
  REQUIRE(Solution().decodeString(s) == expected);
}

TEST_CASE("394ex2", "[394]") {
  const auto s = "3[a2[c]]"s;
  const auto expected = "accaccacc"s;
  REQUIRE(Solution().decodeString(s) == expected);
}

TEST_CASE("394ex3", "[394]") {
  const auto s = "2[abc]3[cd]ef"s;
  const auto expected = "abcabccdcdcdef"s;
  REQUIRE(Solution().decodeString(s) == expected);
}

TEST_CASE("394ex4", "[394]") {
  const auto s = "abc3[cd]xyz"s;
  const auto expected = "abccdcdcdxyz"s;
  REQUIRE(Solution().decodeString(s) == expected);
}