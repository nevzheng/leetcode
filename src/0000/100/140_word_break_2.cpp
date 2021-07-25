// 140_word_break_2
// Nevin Zheng
// 7/25/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using WordVec = vector<string>;
using Dictionary = set<string, less<>>;
using SentenceVec = vector<vector<string_view>>;

void word_break(const Dictionary& dict, string_view word,
                vector<string_view>& path, SentenceVec& sentences) {
  if (dict.count(word)) {
    path.emplace_back(word);
    sentences.emplace_back(path);
    path.pop_back();
  }
  for (auto i = 0U; i < word.size(); i++) {
    auto prefix = word.substr(0, i);
    if (dict.count(prefix) != 0U) {
      path.emplace_back(prefix);
      word_break(dict, word.substr(i), path, sentences);
      path.pop_back();
    }
  }
}

WordVec wordBreak(const string& s, const vector<string>& wordDict) {
  Dictionary dict(begin(wordDict), end(wordDict));
  SentenceVec sentences;
  vector<string_view> path;
  word_break(dict, string_view(s), path, sentences);
  WordVec ans;
  for (auto& v : sentences) {
    string x;
    for (auto i = 0UL; i < v.size(); i++) {
      x += v[i];
      if (i < v.size() - 1) x += ' ';
    }
    ans.push_back(x);
  }
  return ans;
}

TEST_CASE("140ex1", "[140]") {
  const string s = "catsanddog";
  const WordVec word_dict = {"cat", "cats", "and", "sand", "dog"};
  WordVec expected = {"cats and dog", "cat sand dog"};
  sort(begin(expected), end(expected));
  auto v = wordBreak(s, word_dict);
  sort(begin(v), end(v));
  REQUIRE(v == expected);
}

TEST_CASE("140ex2", "[140]") {
  const string s = "pineapplepenapple";
  const WordVec word_dict = {"apple", "pen", "applepen", "pine", "pineapple"};
  WordVec expected = {"pine apple pen apple", "pineapple pen apple",
                      "pine applepen apple"};
  sort(begin(expected), end(expected));
  auto v = wordBreak(s, word_dict);
  sort(begin(v), end(v));
  REQUIRE(v == expected);
}

TEST_CASE("140ex3", "[140]") {
  const string s = "catsandog";
  const WordVec word_dict = {"cats", "dog", "sand", "and", "cat"};
  const WordVec expected = {};
  auto v = wordBreak(s, word_dict);
  sort(begin(v), end(v));
  REQUIRE(v == expected);
}

TEST_CASE("140ex4", "[140]") {
  const string s = "aaaaaaa";
  const WordVec word_dict = {"aaaa", "aa", "a"};
  WordVec expected = {
      "a a a a a a a", "aa a a a a a", "a aa a a a a", "a a aa a a a",
      "aa aa a a a",   "aaaa a a a",   "a a a aa a a", "aa a aa a a",
      "a aa aa a a",   "a aaaa a a",   "a a a a aa a", "aa a a aa a",
      "a aa a aa a",   "a a aa aa a",  "aa aa aa a",   "aaaa aa a",
      "a a aaaa a",    "aa aaaa a",    "a a a a a aa", "aa a a a aa",
      "a aa a a aa",   "a a aa a aa",  "aa aa a aa",   "aaaa a aa",
      "a a a aa aa",   "aa a aa aa",   "a aa aa aa",   "a aaaa aa",
      "a a a aaaa",    "aa a aaaa",    "a aa aaaa"};
  sort(begin(expected), end(expected));
  auto v = wordBreak(s, word_dict);
  sort(begin(v), end(v));
  REQUIRE(v == expected);
}
