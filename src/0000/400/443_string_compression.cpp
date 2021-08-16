// 443_string_compression
// Nevin Zheng
// 8/16/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int compress(vector<char>& chars) {
    auto l = 0UL;
    auto r = 0UL;
    auto len = chars.size();
    while (r < len) {
      auto cur = chars[r];
      auto n = 0UL;
      while (r < len && chars[r] == cur) ++r, ++n;  // Count len
      chars[l++] = cur;                             // Write char
      if (n > 1) {
        auto count = to_string(n);
        for (auto c : count) chars[l++] = c;
      }
    }
    chars.resize(l);
    return chars.size();
  }
};

TEST_CASE("443::1", "[443]") {
  vector<char> chars = {'a', 'a', 'b', 'b', 'c', 'c', 'c'};
  vector<char> expected = {'a', '2', 'b', '2', 'c', '3'};
  auto expected_len = 6;
  auto res = Solution::compress(chars);
  REQUIRE(res == expected_len);
  REQUIRE(std::equal(chars.begin(), chars.begin() + res, expected.begin()));
}

TEST_CASE("443::2", "[443]") {
  vector<char> chars = {'a'};
  vector<char> expected = {'a'};
  auto expected_len = 1;
  auto res = Solution::compress(chars);
  REQUIRE(res == expected_len);
  REQUIRE(std::equal(chars.begin(), chars.begin() + res, expected.begin()));
}

TEST_CASE("443::3", "[443]") {
  vector<char> chars = {'a', 'b', 'b', 'b', 'b', 'b', 'b',
                        'b', 'b', 'b', 'b', 'b', 'b'};
  vector<char> expected = {'a', 'b', '1', '2'};
  auto expected_len = 4;
  auto res = Solution::compress(chars);
  REQUIRE(res == expected_len);
  REQUIRE(std::equal(chars.begin(), chars.begin() + res, expected.begin()));
}

TEST_CASE("443::4", "[443]") {
  vector<char> chars = {'a', 'a', 'a', 'b', 'b', 'a', 'a'};
  vector<char> expected = {'a', '3', 'b', '2', 'a', '2'};
  auto expected_len = 6;
  auto res = Solution::compress(chars);
  REQUIRE(res == expected_len);
  REQUIRE(std::equal(chars.begin(), chars.begin() + res, expected.begin()));
}
