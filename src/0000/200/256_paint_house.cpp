// 256_paint_house
// Nevin Zheng
// 8/29/21
// https://medium.com/@SilentFlame/leetcode-paint-house-dynamic-programming-9253c3b5687c

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static const size_t kRed = 0;
  static const size_t kBlue = 1;
  static const size_t kGreen = 2;

  int paintHouse(const vector<vector<int>>& costs) {
    auto r = costs.size();
    auto c = costs.front().size();
    vector<vector<int>> dp(r, vector<int>(c));
    dp[0] = costs[0];  // Start by painting the first house
    for (auto i = 1UL; i < r; ++i) {
      dp[i][kRed] = costs[i][kRed] + min(dp[i - 1][kBlue], dp[i - 1][kGreen]);
      dp[i][kBlue] = costs[i][kBlue] + min(dp[i - 1][kRed], dp[i - 1][kGreen]);
      dp[i][kGreen] = costs[i][kGreen] + min(dp[i - 1][kRed], dp[i - 1][kBlue]);
    }
    auto& last = dp.back();
    return *min_element(last.begin(), last.end());
  }
};