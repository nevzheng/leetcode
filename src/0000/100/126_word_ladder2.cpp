// 127_word_ladder
// Nevin Zheng
// 7/19/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using AdjList = map<string, set<string>>;
using Dict = set<string>;
using WordList = vector<string>;
using ParentMap = map<string, set<string>>;
using PathVec = vector<vector<string>>;

void neighborSearch(const Dict& dict, AdjList& G, const string& word) {
  for (auto i = 0UL; i < word.size(); i++) {
    auto s = word;  // Create a working copy
    for (char c = 'a'; c <= 'z'; c++) {
      if (c == s.at(i))
        continue;  // Avoid replacing the char if it results in the same word
      s[i] = c;
      if (dict.count(s))
        G[word].insert(s);  // If s exists make A connection between G and s
    }
  }
}

AdjList makeAdjList(const WordList& wordList, const Dict& dict) {
  AdjList g;
  // Iterate over each word and add edges to other words
  for (const auto& word : wordList) neighborSearch(dict, g, word);
  return g;
}

void tracePaths(const ParentMap& parents, vector<string> path,
                const string& targetWord, const string& currentWord,
                const int depth, PathVec& paths) {
  if (depth < 0) return;  // Overflow guard
  if (depth == 0 and currentWord != targetWord) return;

  path.push_back(currentWord);  // Extend path with current Node
  if (depth == 0 and currentWord == targetWord) {
    reverse(begin(path), end(path));
    return paths.push_back(path);
  }
  // Continue to explore Parents
  for (const auto& parent : parents.at(currentWord)) {
    tracePaths(parents, path, targetWord, parent, depth - 1, paths);
  }
}

PathVec findLadders(const string& beginWord, const string& endWord,
                    const WordList& wordList) {
  if (auto it = find(begin(wordList), end(wordList), endWord);
      it == end(wordList))
    return {};
  Dict dict;
  copy(cbegin(wordList), cend(wordList),
       inserter(dict, begin(dict)));  // Speed up Lookup with a hashset
  auto graph = makeAdjList(
      wordList, dict);  // Create an Adjacency list of the graph. If we exceed
                        // memory or time, we can search each node live.
  if (!dict.count(beginWord))
    neighborSearch(dict, graph,
                   beginWord);  // If beginWord is not in the wordList, augment
                                // the graph with an additional node. Only need
                                // forward edges to the graph?
  // Conduct a breadth first search until you find endWord, returning the depth
  // of the word
  int depth = 0;
  int min_depth = INT_MAX;
  ParentMap parents;
  queue<string> q{{beginWord}};
  set<string> visited;
  while (!q.empty()) {
    if (depth > min_depth)
      break;  // Stop Exploring if we exceeded a our minDepth
    auto lvl_sz = q.size();
    while (lvl_sz--) {
      auto curr = q.front();
      q.pop();
      visited.insert(curr);  // Mark Word as visited
      if (curr == endWord) {
        min_depth = min(min_depth, depth);
      }
      for (const auto& w : graph[curr]) {
        if (!visited.count(w)) {
          parents[w].insert(curr);
          q.push(w);  // Insert word if not visited
        }
      }
    }
    depth++;  // Increment the depth
  }
  //
  //  for (const auto& kv : parents) {
  //    fmt::print("'{}': [{}]\n", kv.first, fmt::join(kv.second, ", "));
  //  }
  //
  if (visited.count(endWord)) {
    PathVec ans;
    tracePaths(parents, {}, beginWord, endWord, min_depth, ans);
    sort(begin(ans), end(ans));
    return ans;
  }
  return {};
}

TEST_CASE("126ex1", "[126]") {
  const string begin_word = "hit";
  const string end_word = "cog";
  vector<string> word_list = {"hot", "dot", "dog", "lot", "log", "cog"};
  vector<vector<string>> expected = {{"hit", "hot", "dot", "dog", "cog"},
                                     {"hit", "hot", "lot", "log", "cog"}};
  REQUIRE(findLadders(begin_word, end_word, word_list) == expected);
}
