// 127_word_ladder
// Nevin Zheng
// 7/19/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

using AdjList = map<string, set<string>>;// Could be an unordered set, but that's ok
using Dict = set<string>;
using WordList = vector<string>;
using ParentMap = map<string, set<string>>;
using PathVec = vector<vector<string>>;

void neighborSearch(const Dict &dict, AdjList &G, const string &word) {
    for (auto i = 0; i < word.size(); i++) {
        auto s = word;// Create a working copy
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == s.at(i)) continue;// Avoid replacing the char if it results in the same word
            s[i] = c;
            if (dict.count(s)) G[word].insert(s);// If s exists make A connection between G and s
        }
    }
}

AdjList makeAdjList(const WordList &wordList, const Dict &dict) {
    AdjList G;
    // Iterate over each word and add edges to other words
    for (auto &word : as_const(wordList)) neighborSearch(dict, G, word);
    return G;
}

using Path = vector<string>;


void tracePaths(const ParentMap &parents, vector<string> path, const string &targetWord, const string &currentWord,
                const int depth, PathVec &paths) {
    if (depth == 0 and currentWord != targetWord) return;

    path.push_back(currentWord);// Extend path with current Node
    if (depth == 0 and currentWord == targetWord) {
        reverse(begin(path), end(path));
        return paths.push_back(path);
    }
    // Continue to explore Parents
    if (parents.count(currentWord))
        for (auto &parent : as_const(parents.at(currentWord)))
            tracePaths(parents, path, targetWord, parent, depth - 1, paths);
}

PathVec findLadders(const string &beginWord, const string &endWord, const WordList &wordList) {
    if (auto it = find(begin(wordList), end(wordList), endWord); it == end(wordList)) return {};
    Dict dict;
    copy(cbegin(wordList), cend(wordList), inserter(dict, begin(dict)));// Speed up Lookup with a hashset
    auto G = makeAdjList(wordList, dict);                               // Create an Adjacency list of the graph. If we exceed memory or time, we can search each node live.
    if (!dict.count(beginWord)) neighborSearch(dict, G, beginWord);     // If beginWord is not in the wordList, augment the graph with an additional node. Only need forward edges to the graph?
    // Conduct a breadth first search until you find endWord, returning the depth of the word
    int depth = 0;
    int minDepth = 10'007;
    ParentMap parents;
    queue<string> q{{beginWord}};
    set<string> visited;
    while (!q.empty()) {
        if (depth > minDepth) break;// Stop Exploring if we exceeded a our minDepth
        auto lvlSz = q.size();
        while (lvlSz--) {
            auto curr = q.front();
            q.pop();
            visited.insert(curr);// Mark Word as visited
            if (curr == endWord) { minDepth = min(minDepth, depth); }
            for (auto &w : as_const(G[curr])) {
                if (!visited.count(w)) {
                    parents[w].insert(curr);
                    q.push(w);// Insert word if not visited
                }
            }
        }
        depth++;// Increment the depth
    }
    //
    for (auto [k, v] : as_const(parents)) {
        fmt::print("'{}': [{}]\n", k, fmt::join(v, ", "));
    }
    //
    if (visited.count(endWord)) {
        PathVec ans;
        tracePaths(parents, {}, beginWord, endWord, minDepth, ans);
        sort(begin(ans), end(ans));
        return ans;
    }
    return {};
}


TEST_CASE("126ex1", "[126]") {
    auto beginWord = "hit";
    auto endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    vector<vector<string>> expected = {{"hit", "hot", "dot", "dog", "cog"},
                                       {"hit", "hot", "lot", "log", "cog"}};
    REQUIRE(findLadders(beginWord, endWord, wordList) == expected);
}
