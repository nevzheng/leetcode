// 56_merge_intervals
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static vector<vector<int>> merge(vector<vector<int>>& intervals) {
    // Lexicographically sort intervals
    std::sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged{{intervals.front()}};
    auto head = 0UL;  // Position in merged
    for (auto i = 1UL; i < intervals.size(); ++i) {
      auto& hd = merged[head];
      auto& iv = intervals[i];
      // Merge Overlapping Interval
      if (hd[0] <= iv[0] && iv[0] <= hd[1]) {
        hd = {min(hd[0], iv[0]), max(hd[1], iv[1])};
      } else {
        merged.push_back(iv);
        ++head;
      }
    }
    return merged;
  }
};

TEST_CASE("56::1", "[56]") {
  vector<vector<int>> intervals{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
  vector<vector<int>> expected{{1, 6}, {8, 10}, {15, 18}};
  REQUIRE(Solution::merge(intervals) == expected);
}

TEST_CASE("56::2", "[56]") {
  vector<vector<int>> intervals{{1, 4}, {4, 5}};
  vector<vector<int>> expected{{1, 5}};
  REQUIRE(Solution::merge(intervals) == expected);
}