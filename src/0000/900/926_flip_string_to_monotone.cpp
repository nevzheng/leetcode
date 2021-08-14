// 926_flip_string_to_monotone
// Nevin Zheng
// 8/10/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// We want all zeros in the first part and ones in the second part
// We can use prefix sums to efficiently count the number of flips
// Let P[x] = the number of ones up to a given index i
// To count the number of flips to convert to a monotone string
// with the partition at i. We need to flip P[i] zeros in the front
// and  N - i - (prefix[N] - prefix[i]) zero to ones in the back.
// the second formula is explained:
// Prefix[N] - prefix[i] is the number of one in [i,N]. the len of [i,N]
// is N-i. Prefix[i] is the number of ones, thus. the different is the number
// of zeros. We can iterate through all possible i to determine the number of
// flips
class Solution {
 public:
  static int minFlipsMonoIncr(const string& s) {
    auto n = static_cast<int>(s.size());
    // prefix will contain the number of ones up to a certain index i
    vector<int> pre(n + 1);
    // let pre[0] = 0;
    std::transform_inclusive_scan(s.begin(), s.end(), pre.begin() + 1,
                                  std::plus(),
                                  [](const auto c) { return c - '0'; });
    int min_flips = INT_MAX;
    for (auto i = 0; i <= n; ++i)
      min_flips = min(min_flips, pre[i] + (n - i - (pre[n] - pre[i])));
    return min_flips;
  }
};

TEST_CASE("926ex1", "[926]") {
  const string s = "00110";
  const auto expected = 1;
  REQUIRE(Solution::minFlipsMonoIncr(s) == expected);
}

TEST_CASE("926ex2", "[926]") {
  const string s = "010110";
  const auto expected = 2;
  REQUIRE(Solution::minFlipsMonoIncr(s) == expected);
}

TEST_CASE("926ex3", "[926]") {
  const string s = "00011000";
  const auto expected = 2;
  REQUIRE(Solution::minFlipsMonoIncr(s) == expected);
}