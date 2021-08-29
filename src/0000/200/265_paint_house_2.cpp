// 265_paint_house_2
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  int paintHouse(const vector<vector<int>>& costs) {
    auto r = costs.size();
    auto c = costs.front().size();
    vector<vector<int>> dp(r, vector<int>(c));
    dp[0] = costs[0];  // Start by painting the first house
    for (auto i = 1UL; i < r; ++i) {
      for (auto j = 0UL; j < c; ++j) {
        dp[i][j] += costs[i][j];
        auto min = INT_MAX;
        // min of previous row, excluding current index
        for (auto k = 0UL; k < c; ++k) {
          if (k != j) min = std::min(min, dp[i - 1][k]);
        }
        dp[i][j] += min;
      }
    }
    auto& last = dp.back();
    return *min_element(last.begin(), last.end());
  }
};
TEST_CASE("265::1", "[265]") {
  auto input = {};
  auto expected = {};
  REQUIRE(Solution().foo(input) == expected);
}