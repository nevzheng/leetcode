// 54
// Nevin Zheng
// 8/11/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  const int kRight = 0;
  const int kDown = 1;
  const int kLeft = 2;
  const int kUp = 3;

  [[nodiscard]] vector<int> spiralOrder(
      const vector<vector<int>>& matrix) const {
    auto left = 0;
    auto right = static_cast<int>(matrix.front().size() - 1);
    auto top = 0;
    auto bottom = static_cast<int>(matrix.size() - 1);
    auto direction = kRight;
    vector<int> ans;

    while (left <= right and top <= bottom) {
      if (direction == kRight) {
        for (auto i = left; i <= right; ++i) ans.push_back(matrix[top][i]);
        ++top;
      }
      if (direction == kDown) {
        for (auto j = top; j <= bottom; ++j) ans.push_back(matrix[j][right]);
        --right;
      }
      if (direction == kLeft) {
        for (auto i = right; left <= i; --i) ans.push_back(matrix[bottom][i]);
        --bottom;
      }
      if (direction == kUp) {
        for (auto j = bottom; top <= j; --j) ans.push_back(matrix[j][left]);
        ++left;
      }
      direction = (direction + 1) % 4;
    }
    return ans;
  }
};

TEST_CASE("54_spiral_matrix::1", "[54_spiral_matrix]") {
  const vector<vector<int>> matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const vector<int> expected{1, 2, 3, 6, 9, 8, 7, 4, 5};
  REQUIRE(Solution().spiralOrder(matrix) == expected);
}

TEST_CASE("54_spiral_matrix::2", "[54_spiral_matrix]") {
  const vector<vector<int>> matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
  const vector<int> expected{1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};
  REQUIRE(Solution().spiralOrder(matrix) == expected);
}