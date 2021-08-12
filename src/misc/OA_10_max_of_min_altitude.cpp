// OA_10_max_of_min_altitude
// Nevin Zheng
// 8/10/21

// https://leetcode.com/discuss/interview-question/383669/

// Given a matrix with r rows and c columns, find the maximum score of a path
// starting at [0, 0] and ending at [r-1, c-1]. The score of a path is the
// minimum value in that path. For example, the score of the path 8 → 4 → 5 → 9
// is 4.
//
// Don't include the first or final entry. You can only move either down or
// right at any point in time.
//
// Example 1:
//
// Input:
//[[5, 1],
//  [4, 5]]
//
//  Output: 4
//  Explanation:
//  Possible paths:
//  5 → 1 → 5 => min value is 1
//  5 → 4 → 5 => min value is 4
//  Return the max value among minimum values => max(4, 1) = 4.
//
//  Example 2:
//  Input:
//  [[1, 2, 3]
//   [4, 5, 1]]
//  Output: 4
//              Explanation:
//              Possible paths:
//              1-> 2 -> 3 -> 1
//              1-> 2 -> 5 -> 1
//              1-> 4 -> 5 -> 1
//              So min of all the paths = [2, 2, 4]. Note that we don't include
//              the first and final entry.
//                  Return the max of that, so 4.
//
// Problem analysis: DFS is really easy and quick. O(MN) time, O(M+N) space.
// DP can be a little more challenging to think about. O(MN) S + T

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We will use dynamic programming to solve.
 * let dp[i][j] be the max score for the sub square G[0][0] to G[i][j]
 * the min path from left is min_left = min(dp[i][j-1], G[i][j])
 * the min path from right is min_right = min(dp[i-1][j], G[i][j])
 * the max score will be dp[i][j] = max(min_left, min_right)
 *
 * O(mn) time and space
 * @param grid
 * @return
 */
// int maxOfMinPaths(vector<vector<int>>& grid) {
//   auto m = grid.size();
//   auto n = grid.front().size();
//   // dp[i][j] = max score for grid[i][j]
//   vector<vector<int>> dp(m, vector(n, INT_MAX));
//   grid[0][0] = INT_MAX;  // Exclude First Entry
//   // First Row Base Case
//   for (auto j = 1UL; j < m; ++j) dp[j][0] = min(dp[j - 1][0], grid[j][0]);
//   // First Col Base Case
//   for (auto i = 1UL; i < n; ++i) dp[0][i] = min(dp[0][i - 1], grid[0][i]);
//
//   for (auto i = 1UL; i < m; ++i) {
//     for (auto j = 1UL; j < n; ++j) {
//       if ((i == m - 1) and (j == n - 1)) {
//         dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);  // Skip Last Entry
//       } else {
//         auto min_left = min(dp[i][j - 1], grid[i][j]);
//         auto min_up = min(dp[i - 1][j], grid[i][j]);
//         dp[i][j] = max(min_left, min_up);
//       }
//     }
//   }
//   return dp.back().back();
// }

/**
 * We use a DFS to trace all paths, tracking the min value along each path.
 * When we get to the end, we take the max.
 * Time O(MN): We visit all the squares at least once.
 * If you take a small example and trace all the paths you'll see that this is
 * the case
 * Space O(M+N): Our DFS is limited by the max lenth of a path which is M+N
 * @param grid
 * @param m
 * @param n
 * @param i
 * @param j
 * @param score
 * @param max_score
 */
void dfs(const vector<vector<int>>& grid, int m, int n, int i, int j, int score,
         int& max_score) {
  if (i >= m || j >= n) return;    // Bounds Check
  if (i == m - 1 && j == n - 1) {  // Last Square
    max_score = max(max_score, score);
    return;
  }
  score = min(score, grid[i][j]);
  dfs(grid, m, n, i, j + 1, score, max_score);  // Call Right
  dfs(grid, m, n, i + 1, j, score, max_score);  // Call Down
}

int maxOfMinPaths(vector<vector<int>>& grid) {
  auto m = static_cast<int>(grid.size());
  auto n = static_cast<int>(grid.front().size());
  int max_score = 0;
  grid[0][0] = INT_MAX;
  dfs(grid, m, n, 0, 0, INT_MAX, max_score);
  return max_score;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-magic-numbers"
TEST_CASE("OA::10::1", "[oa10]") {
  vector<vector<int>> grid = {{5, 1}, {4, 5}};
  REQUIRE(maxOfMinPaths(grid) == 4);
}
#pragma clang diagnostic pop

TEST_CASE("OA::10::2", "[oa10]") {
  vector<vector<int>> grid = {{1, 2, 3}, {4, 5, 1}};
  REQUIRE(maxOfMinPaths(grid) == 4);
}

TEST_CASE("OA::10::3", "[oa10]") {
  vector<vector<int>> grid = {{5, 1, 7}, {4, 8, 5}};
  REQUIRE(maxOfMinPaths(grid) == 4);
}

TEST_CASE("OA::10::4", "[oa10]") {
  vector<vector<int>> grid = {{1, 9, 9}, {9, 9, 9}, {9, 9, 9}};
  REQUIRE(maxOfMinPaths(grid) == 9);
}

TEST_CASE("OA::10::5", "[oa10]") {
  vector<vector<int>> grid = {{10, 7, 3}, {12, 11, 9}, {1, 2, 8}};
  REQUIRE(maxOfMinPaths(grid) == 9);
}

TEST_CASE("OA::10::6", "[oa10]") {
  vector<vector<int>> grid = {{20, 20, 3}, {20, 3, 20}, {3, 20, 20}};
  REQUIRE(maxOfMinPaths(grid) == 3);
}