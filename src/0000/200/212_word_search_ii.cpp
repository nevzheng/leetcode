// 212_word_search_ii
// Nevin Zheng
// 7/30/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * First we Preprocess the word list creating a set of words
 * to quickly detect if a prefix is valid
 * next we create a set of all prefixes. This set will help prune
 * the search space as we should stop searching if we reach an invalid
 * prefixes. using maps and sets is space inefficient a more optimal solution
 * would be to use a trie
 * time m*n * 4^maxlen word . space: N* maxlenword^2
 */
using Board = vector<vector<char>>;
using PrefixSet = unordered_set<string>;
using Dictionary = unordered_set<string>;
class Solution {
 public:
  PrefixSet prefixes_;
  Dictionary dict_;
  set<string> found_;
  vector<vector<bool>> visited_;
  int rows_;
  int cols_;

  void dfs(const Board& board, int i, int j, string prefix) {
    if (i < 0 or i >= rows_ or  // invalid row
        j < 0 or j >= cols_ or  // invalid col
        visited_[i][j]) {
      return;
    }
    prefix += board[i][j];
    if (!prefixes_.count(prefix)) return;  // Invalid Prefix, stop search

    visited_[i][j] = true;
    if (dict_.count(prefix)) found_.insert(prefix);  // Insert the word
    // Continue searching
    dfs(board, i + 1, j, prefix);
    dfs(board, i - 1, j, prefix);
    dfs(board, i, j + 1, prefix);
    dfs(board, i, j - 1, prefix);

    visited_[i][j] = false;  // Free Cell for other traversals
  }

  vector<string> findWords(const Board& board, const vector<string>& words) {
    // Storing Prefixes will help us prune paths. It informs the search that
    // a path is worth exploring
    // using hash maps for this is memory intensive
    // a more optimized solution would be to use a trie;
    for (const auto& word : words) {
      dict_.insert(word);
      string pref;
      for (auto c : word) {
        pref += c;
        prefixes_.insert(pref);
      }
    }
    rows_ = static_cast<int>(board.size());
    cols_ = static_cast<int>(board.front().size());

    visited_ = vector(rows_, vector(cols_, false));

    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < cols_; j++) {
        dfs(board, i, j, "");
      }
    }
    vector<string> ans;
    ans.reserve(found_.size());
    copy(begin(found_), end(found_), back_inserter(ans));
    return ans;
  }
};

TEST_CASE("212ex1", "[212]") {
  const Board board = {{'o', 'a', 'a', 'n'},
                       {'e', 't', 'a', 'e'},
                       {'i', 'h', 'k', 'r'},
                       {'i', 'f', 'l', 'v'}};
  const vector<string> words = {"oath", "pea", "eat", "rain"};
  const vector<string> expected = {"eat", "oath"};
  REQUIRE(Solution().findWords(board, words) == expected);
}

TEST_CASE("212ex2", "[212]") {
  const Board board = {{'a', 'b'}, {'c', 'd'}};
  const vector<string> words = {"abcb"};
  const vector<string> expected = {};
  REQUIRE(Solution().findWords(board, words) == expected);
}