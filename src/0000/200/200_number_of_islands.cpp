// 200_number_of_islands
// Nevin Zheng
// 8/9/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static constexpr char kVisited = '2';
  static constexpr char kLand = '1';
  static constexpr char kWater = '0';
  void dfs(vector<vector<char>>& grid, int m, int n, int i, int j) {
    if (i < 0 or i >= m or j < 0 or j >= n) return;  // Bounds check
    // Skip Water and Visited
    if (grid[i][j] == kWater or grid[i][j] == kVisited) return;
    grid[i][j] = kVisited;      // Mark Land As Visited;
    dfs(grid, m, n, i - 1, j);  // North
    dfs(grid, m, n, i, j - 1);  // West
    dfs(grid, m, n, i + 1, j);  // South
    dfs(grid, m, n, i, j + 1);  // East
  }

  int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    int m = static_cast<int>(grid.size());
    int n = static_cast<int>(grid.front().size());
    for (auto i = 0; i < n; ++i) {
      for (auto j = 0; j < m; ++j) {
        if (grid[i][j] == kLand) {
          dfs(grid, m, n, i, j);
          ++count;
        }
      }
    }
    return count;
  }
};

TEST_CASE("200ex1", "[200]") {
  vector<vector<char>> grid = {{'1', '1', '1', '1', '0'},
                               {'1', '1', '0', '1', '0'},
                               {'1', '1', '0', '0', '0'},
                               {'0', '0', '0', '0', '0'}};
  auto expected = 1;
  REQUIRE(Solution().numIslands(grid) == expected);
}

TEST_CASE("200ex2", "[200]") {
  vector<vector<char>> grid = {{'1', '1', '0', '0', '0'},
                               {'1', '1', '0', '0', '0'},
                               {'0', '0', '1', '0', '0'},
                               {'0', '0', '0', '1', '1'}};
  auto expected = 3;
  REQUIRE(Solution().numIslands(grid) == expected);
}