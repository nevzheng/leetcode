// 1088_confusing_number_22
// Nevin Zheng
// 7/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 private:
  static constexpr int kBase = 10;
  const map<char, char> rotated_{
      {'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
  const vector<int> valid_{0, 1, 6, 8, 9};
  int count_ = 0;

  bool isConfusing(int N) {
    auto num = to_string(N);  // Convert to a string
    // all the digits of the number have to be 0,1,6,8,9
    if (!all_of(cbegin(num), cend(num),
                [&](auto c) { return rotated_.count(c); })) {
      return false;
    }
    // Check for rotational symmetry. Number must be different
    string rotated;
    transform(crbegin(num), crend(num), back_inserter(rotated),
              [&](auto c) { return rotated_.at(c); });
    return num != rotated;
  }

  void dfs(int cur, int digit, int max_val) {
    cur = cur * kBase + digit;
    if (cur > max_val) return;
    if (Solution::isConfusing(cur)) count_++;
    for (const auto k : valid_) dfs(cur, k, max_val);
  }

 public:
  int confusingNumberII(int N) {
    for (const auto k : valid_) {
      if (k != 0) dfs(0, k, N);
    }
    return count_;
  }
};

TEST_CASE("1088ex1", "[1088]") {
  const auto n = 20;
  const auto expected = 6;
  REQUIRE(Solution().confusingNumberII(n) == expected);
}

TEST_CASE("1088ex2", "[1088]") {
  const auto n = 100;
  const auto expected = 19;
  REQUIRE(Solution().confusingNumberII(n) == expected);
}

TEST_CASE("1088ex3", "[1088]") {
  const auto n = 10'000;
  const auto expected = 587;
  REQUIRE(Solution().confusingNumberII(n) == expected);
}

TEST_CASE("1088ex4", "[1088]") {
  const auto n = 1e6;
  const auto expected = 15427;
  REQUIRE(Solution().confusingNumberII(n) == expected);
}