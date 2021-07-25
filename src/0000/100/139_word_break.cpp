// 139_word_break
// Nevin Zheng
// 7/25/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using WordList = vector<string>;
using Dictionary = set<string, less<>>;

// bool word_break(const Dictionary& dict, const string& word) {
bool word_break(const Dictionary& dict, vector<bool>& visited, size_t pos,
                string_view word) {
  if (visited[pos]) return false;
  if (dict.count(word)) return true;
  for (auto i = 0U; i < word.size(); i++) {
    if (dict.count(word.substr(0, i)) != 0U &&
        word_break(dict, visited, pos + i, word.substr(i)))
      return true;
  }
  visited[pos] = true;
  return false;
}

bool wordBreak(const string& s, const vector<string>& word_dict) {
  Dictionary dict(begin(word_dict), end(word_dict));
  vector<bool> visited(s.size());
  return word_break(dict, visited, 0, string_view(s));
}

TEST_CASE("139ex1", "[139]") {
  const string s = "leetcode";
  const WordList word_dict = {"leet", "code"};
  const auto expected = true;
  REQUIRE(wordBreak(s, word_dict) == expected);
}

TEST_CASE("139ex2", "[139]") {
  const string s = "applepenapple";
  const WordList word_dict = {"apple", "pen"};
  const auto expected = true;
  REQUIRE(wordBreak(s, word_dict) == expected);
}

TEST_CASE("139ex3", "[139]") {
  const string s = "catsandog";
  const WordList word_dict = {"cats", "dog", "sand", "and", "cat"};
  const auto expected = false;
  REQUIRE(wordBreak(s, word_dict) == expected);
}

TEST_CASE("139ex4", "[139]") {
  const string s =
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaab";
  const WordList word_dict = {"a",         "aa",        "aaa",     "aaaa",
                              "aaaaa",     "aaaaaa",    "aaaaaaa", "aaaaaaaa",
                              "aaaaaaaaa", "aaaaaaaaaa"};
  const auto expected = false;
  REQUIRE(wordBreak(s, word_dict) == expected);
}