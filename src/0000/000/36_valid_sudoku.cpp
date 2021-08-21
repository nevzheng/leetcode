// 36_valid_sudoku
// Nevin Zheng
// 8/21/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static bool isValidSudoku(const vector<vector<char>>& board) {
    auto r = board.size();
    auto c = board.front().size();
    vector<bitset<9>> rows(9);
    vector<bitset<9>> cols(9);

    vector<vector<bitset<9>>> squares(3, vector<bitset<9>>(3));
    for (auto i = 0UL; i < r; ++i) {
      for (auto j = 0UL; j < c; ++j) {
        if (!isdigit(board[i][j])) continue;  // Skip Empty Cells
        auto val = board[i][j] - '0' - 1;     // Convert to an index

        if (rows[i].test(val)) return false;  // Conflict Detected
        rows[i].set(val);                     // Set Row

        if (cols[j].test(val)) return false;  // Conflict Detected
        cols[j].set(val);                     // Set col

        if (squares[i / 3][j / 3].test(val)) return false;  // Check Square
        squares[i / 3][j / 3].set(val);                     // Set Square
      }
    }
    return true;
  }
};

TEST_CASE("36::1", "[36]") {
  const vector<vector<char>> board{
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  const auto expected = true;
  REQUIRE(Solution::isValidSudoku(board) == expected);
}

TEST_CASE("36::2", "[36]") {
  const vector<vector<char>> board{
      {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  const auto expected = false;
  REQUIRE(Solution::isValidSudoku(board) == expected);
}