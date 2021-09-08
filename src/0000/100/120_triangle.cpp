// 120_triangle
// Nevin Zheng
// 9/8/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int minimumTotal(vector<vector<int>>& triangle) {
    auto len = static_cast<int>(size(triangle));
    // start from level 1 till the bottom-most level. Each time determine the
    // best path to arrive at current cell
    for (auto level = 1; level < len; level++)
      // triangle[level].size() == level + 1 (level starts from 0)
      for (int i = 0; i <= level; i++) {
        // Previous level and same index
        int same_idx = min(i, static_cast<int>(size(triangle[level - 1])) - 1);
        int prev_idx = max(i - 1, 0);  // Previous level and index-1
        triangle[level][i] +=
            min(triangle[level - 1][same_idx], triangle[level - 1][prev_idx]);
      }
    // finally, return the last element of the bottom level
    return *min_element(begin(triangle.back()), end(triangle.back()));
  }
};
