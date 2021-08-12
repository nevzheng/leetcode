// 59_spiral_matrix_2
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

  [[nodiscard]] vector<vector<int>> generateMatrix(int n) const {
    vector matrix(n, vector(n, 0));
    int lft = 0;
    int rgt = n - 1;
    int top = 0;
    int bot = n - 1;
    int direction = kRight;
    int x = 1;
    while (lft <= rgt and top <= bot) {
      if (direction == kRight) {
        for (auto i = lft; i <= rgt; ++i) matrix[top][i] = x++;
        ++top;
      }
      if (direction == kDown) {
        for (auto i = top; i <= bot; ++i) matrix[i][rgt] = x++;
        --rgt;
      }
      if (direction == kLeft) {
        for (auto i = rgt; i >= lft; --i) matrix[bot][i] = x++;
        --bot;
      }
      if (direction == kUp) {
        for (auto i = bot; i >= top; --i) matrix[i][lft] = x++;
        ++lft;
      }
      direction = (direction + 1) % 4;
    }
    return matrix;
  }
};

TEST_CASE("59::1", "[59]") {
  const auto n = 3;
  const vector<vector<int>> expected{{1, 2, 3}, {8, 9, 4}, {7, 6, 5}};
  REQUIRE(Solution().generateMatrix(n) == expected);
}