// string_distance
// https://leetcode.com/discuss/interview-experience/229559/google-onsite-interview-questions-sde-5-rounds
// Nevin Zheng
// 8/9/21

// Given a string X and a dictionary of words Y, return a set of words in Y that
// are at most one character different from X.
//
// Follow-up questions:
// What is the best data structure for this algorithm
// trie, hashmap

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * First we will convert the dict into an unordered set for rapid membership
 * lookup. This will take O(N) time and space where N is the size of the dict.
 * We will be able to perform lookups in constant time.
 *
 * We will then compute all possible strings with a 1 character difference
 * from x. This will take O(m) time where m is the len of the string
 * Given a constant alphabet size.
 * For each computed string, we will check if its in the dict in constant time
 * We'll use a set to filter out duplicates
 * @param dict
 * @param x
 * @return
 */
vector<string> closestStrings(const vector<string>& word_list, string x) {
  unordered_set dict(word_list.begin(), word_list.end());
  set<string> ans;
  // We will need to consider all strings with edit distances of 1
  // This involves: insertions, removals, and substitutions
  // Consider all Insertions
  for (auto i = 0UL; i <= x.size(); ++i) {
    // This procedure takes linear time, could make more efficient
    auto pref = x.substr(0, i);
    auto suf = x.substr(i);
    for (auto c = 'a'; c <= 'z'; ++c) {
      auto cur = pref + c + suf;
      //      fmt::print("{} + {} + {} = {}\n", pref, c, suf, cur);
      if (dict.count(cur)) ans.insert(cur);
    }
  }
  // Consider all Deletions
  for (auto i = 0UL; i < x.size(); ++i) {
    // This procedure takes linear time, could make more efficient
    auto pref = x.substr(0, i);
    auto suf = x.substr(i + 1);
    auto cur = pref + suf;
    fmt::print("{} + {} = {}\n", pref, suf, cur);
    if (dict.count(cur)) ans.insert(cur);
  }
  // Consider all Substitutions
  for (auto i = 0UL; i < x.size(); ++i) {
    auto orig = x[i];  // Stash the char
    for (auto c = 'a'; c <= 'z'; ++c) {
      if (c == orig) continue;  // Skip the word itself
      x[i] = c;                 // substitute the character
      if (dict.count(x)) ans.insert(x);
    }
    x[i] = orig;  // Reset the char
  }
  return vector(ans.begin(), ans.end());  // output the result
}

TEST_CASE("misc::string_distance::1", "[strdist1]") {
  const vector<string> words = {"cars", "tar", "expulsion", "temporary", "ar"};
  const string x = "car";
  const vector<string> expected = {"ar", "cars", "tar"};
  REQUIRE(closestStrings(words, x) == expected);
}