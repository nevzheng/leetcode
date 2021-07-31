// 42_trapping_rain_water
// Nevin Zheng
// 7/31/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int trap(const vector<int>& H) {
    auto len = static_cast<int>(H.size());
    stack<int> max_stk;
    vector<int> l_min(len);
    vector<int> r_min(len);
    vector<int> water(len);

    // Forward Pass for determining the max value to the left
    for (auto i = 0; i < len; i++) {
      while (!max_stk.empty() and max_stk.top() <= H[i]) max_stk.pop();
      l_min[i] = max_stk.empty() ? 0 : max_stk.top();
      if (max_stk.empty() || H[i] >= max_stk.top()) max_stk.push(H[i]);
    }
    max_stk = {};  // Clear the stack for next pass
    // Reverse Pass for determining the min value to the right
    for (auto i = len - 1; i >= 0; i--) {
      while (!max_stk.empty() and max_stk.top() <= H[i]) max_stk.pop();
      r_min[i] = max_stk.empty() ? 0 : max_stk.top();
      if (max_stk.empty() || H[i] >= max_stk.top()) max_stk.push(H[i]);
    }
    auto idx = -1;
    return std::transform_reduce(begin(l_min), end(l_min), begin(r_min), 0,
                                 plus<>(), [&](const auto L, const auto R) {
                                   ++idx;
                                   if (!L or !R) return 0;
                                   return min(L, R) - H[idx];
                                 });
  }
};

TEST_CASE("42ex1", "[42]") {
  const vector height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  const auto expected = 6;
  REQUIRE(Solution().trap(height) == expected);
}

TEST_CASE("42ex2", "[42]") {
  const vector height{4, 2, 0, 3, 2, 5};
  const auto expected = 9;
  REQUIRE(Solution().trap(height) == expected);
}
