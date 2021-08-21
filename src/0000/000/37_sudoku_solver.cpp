// 37_sudoku_solver
// Nevin Zheng
// 8/21/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  constexpr static size_t kSize = 9;
  using Set = bitset<kSize>;
  using Board = vector<vector<char>>;

  vector<Set> rows_;
  vector<Set> cols_;
  vector<vector<Set>> squares_;

  Solution() : rows_(kSize), cols_(kSize), squares_(3, vector<Set>(3)) {}

  static pair<size_t, size_t> nextIndex(size_t r, size_t c) {
    if (c == kSize - 1) return {r + 1, 0};
    return {r, (c + 1) % kSize};
  }

  bool solve(size_t r, size_t c, Board& board) {
    if (r >= kSize) return true;  // Goal Reached
    auto [x, y] = nextIndex(r, c);
    if (isdigit(board[r][c])) {  // Fixed Digit, Skip
      return solve(x, y, board);
    }
    for (auto i = 0UL; i < kSize; ++i) {  // Try all possibilities
      if (valid(r, c, i)) {
        place(r, c, i);  // Place Val
        board[r][c] = i + '1';
        if (solve(x, y, board)) return true;  // Call
        pop(r, c, i);                         // Remove Val
      }
    }
    board[r][c] = '.';  // reset to blank
    return false;       // No Solution Found
  }

  bool valid(size_t r, size_t c, size_t val) {
    if (rows_[r].test(val)) return false;
    if (cols_[c].test(val)) return false;
    if (squares_[r / 3][c / 3].test(val)) return false;
    return true;
  }

  void place(size_t r, size_t c, size_t val) {
    rows_[r].set(val);
    cols_[c].set(val);
    squares_[r / 3][c / 3].set(val);
  }

  void pop(size_t r, size_t c, size_t val) {
    rows_[r].reset(val);
    cols_[c].reset(val);
    squares_[r / 3][c / 3].reset(val);
  }

  void solveSudoku(Board& board) {
    for (auto i = 0UL; i < kSize; ++i) {
      for (auto j = 0UL; j < kSize; ++j) {
        if (!isdigit(board[i][j])) continue;
        auto val = board[i][j] - '1';
        rows_[i].set(val);
        cols_[j].set(val);
        squares_[i / 3][j / 3].set(val);
      }
    }
    solve(0, 0, board);
  }
};

TEST_CASE("37::1", "[37]") {
  vector<vector<char>> board{{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                             {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                             {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                             {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                             {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                             {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                             {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                             {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                             {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  vector<vector<char>> expected{{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
                                {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
                                {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
                                {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
                                {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
                                {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
                                {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
                                {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
                                {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};
  Solution().solveSudoku(board);
  REQUIRE(board == expected);
}