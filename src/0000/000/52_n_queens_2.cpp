// 52_n_queens_2
// Nevin Zheng
// 9/6/21

#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
  // Keep track of where queens have already been places
  // Queens cannot occupy the same row, col, or upward/downward diagonals
  set<int> cols_;  // Columns
  set<int> up_;    // Upward Diagonals
  set<int> down_;  // Downward Diagonals
  int count_{0};

  void solve(int n, int row) {
    if (row >= n) {
      ++count_;
      return;
    }
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
      solve(n, row + 1);       // Recurse to next row
      cols_.erase(col);        // Free Col
      up_.erase(up_id);        // Free Up Diagonal
      down_.erase(down_id);    // Free Down Diagonal
    }
  }

  int totalNQueens(int n) {
    solve(n, 0);
    return count_;
  }
};
