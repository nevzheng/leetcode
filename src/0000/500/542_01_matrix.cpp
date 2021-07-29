// 542_01_matrix
// Nevin Zheng
// 7/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// 2D Vector Representing the binary matrix
using Matrix = vector<vector<int>>;

/**
 * One valid, given solution is to use BFS.
 * Don't BFS starting from ones start from 0's and update the
 * distance of ones you encounter.
 * only explore cells if you the distance can be improved.
 *
 * This is a DP solution. We need two passes to see if answer can
 * be improved from top left and them bottom right
 */
class Solution {
 public:
  vector<vector<int>> updateMatrix(const vector<vector<int>>& mat) {
    auto rows = static_cast<int>(mat.size());
    auto cols = static_cast<int>(mat.front().size());
    Matrix dist(rows, vector(cols, INT16_MAX));
    // First Pass Check from top left
    for (auto m = 0; m < rows; m++) {
      for (auto n = 0; n < cols; n++) {
        if (mat[m][n] == 0) {
          dist[m][n] = 0;
        } else {
          if (m > 0) dist[m][n] = min(dist[m][n], dist[m - 1][n] + 1);
          if (n > 0) dist[m][n] = min(dist[m][n], dist[m][n - 1] + 1);
        }
      }
    }
    // Second Pass, check from bottom right
    for (auto m = rows - 1; m >= 0; m--) {
      for (auto n = cols - 1; n >= 0; n--) {
        if (mat[m][n] == 0) {
          dist[m][n] = 0;
        } else {
          if (m < rows - 1) dist[m][n] = min(dist[m][n], dist[m + 1][n] + 1);
          if (n < cols - 1) dist[m][n] = min(dist[m][n], dist[m][n + 1] + 1);
        }
      }
    }
    return dist;
  }
};

TEST_CASE("542ex1", "[542]") {
  const Matrix input = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  const Matrix expected = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  REQUIRE(Solution().updateMatrix(input) == expected);
}

TEST_CASE("542ex2", "[542]") {
  const Matrix input = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
  const Matrix expected = {{0, 0, 0}, {0, 1, 0}, {1, 2, 1}};
  REQUIRE(Solution().updateMatrix(input) == expected);
}