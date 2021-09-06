// 51_n_queens
// Nevin Zheng
// 9/6/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  // Keep track of where queens have already been places
  // Queens cannot occupy the same row, col, or upward/downward diagonals
  set<int> cols_;  // Columns
  set<int> up_;    // Upward Diagonals
  set<int> down_;  // Downward Diagonals
  vector<string> board_;
  vector<vector<string>> results_;

  void solve(int n, int row) {
    if (row >= n) return results_.push_back(board_);  // All Queens Placed
    for (auto col = 0; col < n; ++col) {
      auto up_id = row + col;
      auto down_id = row - col;
      // Conflict Detected, skip
      if (cols_.count(col) || up_.count(up_id) || down_.count(down_id)) {
        continue;
      }
      cols_.emplace(col);      // Mark Col
      up_.emplace(up_id);      // Mark Up
      down_.emplace(down_id);  // Mark Down
      board_[row][col] = 'Q';  // Place Queen
      solve(n, row + 1);       // Recurse to next row
      board_[row][col] = '.';  // Clear Queen
      cols_.erase(col);        // Free Col
      up_.erase(up_id);        // Free Up Diagonal
      down_.erase(down_id);    // Free Down Diagonal
    }
  }

  vector<vector<string>> solveNQueens(int n) {
    board_ = vector(n, string(n, '.'));  // Initial board
    solve(n, 0);
    return results_;
  }
};

TEST_CASE("51::1", "[51]") {
  const auto n = 4;
  vector<vector<string>> expected = {{".Q..", "...Q", "Q...", "..Q."},
                                     {"..Q.", "Q...", "...Q", ".Q.."}};
  REQUIRE(Solution().solveNQueens(n) == expected);
}