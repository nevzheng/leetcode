// 79_word_search
// Nevin Zheng
// 7/30/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// Alternate cleaner version. A little less efficient since it makes
// a invalid calls
// using Board = vector<vector<char>>;
// using VisSet = vector<vector<bool>>;
// class Solution {
// public:
//  bool dfs(const Board& board, const int rows, const int cols, VisSet&
//  visited,
//           string_view suffix, int i, int j) {
//    if (i < 0 or i >= rows or           // Invalid Row
//        j < 0 or j >= cols or           // invalid Col
//        visited[i][j] or                // Already visited
//        suffix.front() != board[i][j])  // invalid char
//      return false;
//
//    if (suffix.size() == 1) return true;  // Last Char and matched, return
//    true
//
//    // Continue Exploring
//    suffix.remove_prefix(1);
//    visited[i][j] = true;  // Mark Current Cell as Visited
//    auto result = dfs(board, rows, cols, visited, suffix, i + 1, j) or
//                  dfs(board, rows, cols, visited, suffix, i - 1, j) or
//                  dfs(board, rows, cols, visited, suffix, i, j + 1) or
//                  dfs(board, rows, cols, visited, suffix, i, j - 1);
//    visited[i][j] = false;  // Pop Cell from visited to allow other paths to
//    use return result;
//  }
//
//  bool exist(const Board& board, const string& word) {
//    int rows = static_cast<int>(board.size());
//    int cols = static_cast<int>(board.front().size());
//    VisSet visited(rows, vector(cols, false));
//    for (auto i = 0; i < rows; i++) {
//      for (auto j = 0; j < cols; j++) {
//        if (dfs(board, rows, cols, visited, word, i, j)) return true;
//      }
//    }
//    return false;
//  }
//};

using Board = vector<vector<char>>;
using VisSet = vector<vector<bool>>;
class Solution {
 public:
  bool dfs(const Board& board, const int rows, const int cols, VisSet& visited,
           const string_view& suffix, int i, int j) {
    if (suffix.front() != board[i][j]) return false;  // Reject Invalid Strings
    if (suffix.size() == 1) return true;  // Last Char and matched, return true
    auto nxt = suffix;
    nxt.remove_prefix(1);
    visited[i][j] = true;  // Mark Current Cell as Visited
    if (i + 1 < rows and !visited[i + 1][j] and
        dfs(board, rows, cols, visited, nxt, i + 1, j)) {
      return true;
    }
    if (i - 1 >= 0 and !visited[i - 1][j] and
        dfs(board, rows, cols, visited, nxt, i - 1, j)) {
      return true;
    }
    if (j + 1 < cols and !visited[i][j + 1] and
        dfs(board, rows, cols, visited, nxt, i, j + 1)) {
      return true;
    }
    if (j - 1 >= 0 and !visited[i][j - 1] and
        dfs(board, rows, cols, visited, nxt, i, j - 1)) {
      return true;
    }
    visited[i][j] = false;  // Pop Cell from visited to allow other paths to use
    return false;
  }

  bool exist(const Board& board, const string& word) {
    int rows = static_cast<int>(board.size());
    int cols = static_cast<int>(board.front().size());
    VisSet visited(rows, vector(cols, false));
    for (auto i = 0; i < rows; i++) {
      for (auto j = 0; j < cols; j++) {
        if (dfs(board, rows, cols, visited, word, i, j)) return true;
      }
    }
    return false;
  }
};

TEST_CASE("79ex1", "[79]") {
  const Board board = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  const string word = "ABCCED";
  const auto expected = true;
  REQUIRE(Solution().exist(board, word) == expected);
}

TEST_CASE("79ex2", "[79]") {
  const Board board = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  const string word = "ABCCED";
  const auto expected = true;
  REQUIRE(Solution().exist(board, word) == expected);
}

TEST_CASE("79ex3", "[79]") {
  const Board& board = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  const string word = "ABCB";
  const auto expected = false;
  REQUIRE(Solution().exist(board, word) == expected);
}

TEST_CASE("79ex4", "[79]") {
  const Board& board = {{'a'}};
  const string word = "a";
  const auto expected = true;
  REQUIRE(Solution().exist(board, word) == expected);
}