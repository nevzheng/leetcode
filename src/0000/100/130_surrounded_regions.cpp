// 130_surrounded_regions
// Nevin Zheng
// 8/16/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  void fill(vector<vector<char>>& board, vector<vector<bool>>& visited, int r,
            int c, int i, int j, char from, char to) {
    // OOB or invalid char
    if (i < 0 || i >= r || j < 0 || j >= c ||  // OOB
        visited[i][j] ||                       // Visited
        board[i][j] != from) {                 // Invalid char
      return;
    }
    visited[i][j] = true;
    fill(board, visited, r, c, i - 1, j, from, to);
    fill(board, visited, r, c, i + 1, j, from, to);
    fill(board, visited, r, c, i, j - 1, from, to);
    fill(board, visited, r, c, i, j + 1, from, to);
    board[i][j] = to;
  }

  void solve(vector<vector<char>>& board) {
    auto r = static_cast<int>(board.size());
    auto c = static_cast<int>(board.front().size());
    vector<vector<bool>> visited(r, vector<bool>(c));
    // Flip O component on first row to '#
    for (auto j = 0; j < c; ++j)
      if (!visited[0][j] && board[0][j] == 'O')
        fill(board, visited, r, c, 0, j, 'O', '#');

    // Flip O component on last row to '#
    for (auto j = 0; j < c; ++j)
      if (!visited[r - 1][j] && board[r - 1][j] == 'O')
        fill(board, visited, r, c, r - 1, j, 'O', '#');

    // Flip O component in first col to #
    for (auto i = 0; i < r; ++i)
      if (!visited[i][0] && board[i][0] == 'O')
        fill(board, visited, r, c, i, 0, 'O', '#');

    // Flip O component in last col to #
    for (auto i = 0; i < r; ++i)
      if (!visited[i][c - 1] && board[i][c - 1] == 'O')
        fill(board, visited, r, c, i, c - 1, 'O', '#');

    // DFS all O's to X
    for (auto i = 0; i < r; ++i) {
      for (auto j = 0; j < c; ++j) {
        if (!visited[i][j] && board[i][j] == 'O')
          fill(board, visited, r, c, i, j, 'O', 'X');
      }
    }
    // Flip all '#' to 'O'
    for (auto i = 0; i < r; ++i) {
      for (auto j = 0; j < c; ++j) {
        board[i][j] = board[i][j] == '#' ? 'O' : board[i][j];
      }
    }
  }
};

TEST_CASE("130::1", "[130]") {
  vector<vector<char>> board{{'X', 'X', 'X', 'X'},
                             {'X', 'O', 'O', 'X'},
                             {'X', 'X', 'O', 'X'},
                             {'X', 'O', 'X', 'X'}};
  vector<vector<char>> expected{{'X', 'X', 'X', 'X'},
                                {'X', 'X', 'X', 'X'},
                                {'X', 'X', 'X', 'X'},
                                {'X', 'O', 'X', 'X'}};
  Solution().solve(board);
  REQUIRE(board == expected);
}