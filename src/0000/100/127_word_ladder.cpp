//// 127_word_ladder
//// Nevin Zheng
//// 7/19/21
//
//#include <catch2/catch.hpp>
//#include <fmt/format.h>
//
//#include <algorithm>
//#include <map>
//#include <queue>
//#include <set>
//#include <unordered_set>
//#include <vector>
//
//using namespace std;
//
//using AdjList = map<string, set<string>>;// Could be an unordered set, but that's ok
//using Dict = set<string>;
//using WordList = vector<string>;
//
//void neighborSearch(const Dict &dict, AdjList &G, const string &word) {
//    for (auto i = 0; i < word.size(); i++) {
//        auto s = word;// Create a working copy
//        for (char c = 'a'; c <= 'z'; c++) {
//            if (c == s.at(i)) continue;// Avoid replacing the char if it results in the same word
//            s[i] = c;
//            if (dict.count(s)) G[word].insert(s);// If s exists make A connection between G and s
//        }
//    }
//}
//
//AdjList makeAdjList(const WordList &wordList, const Dict &dict) {
//    AdjList G;
//    // Iterate over each word and add edges to other words
//    for (auto &word : as_const(wordList)) neighborSearch(dict, G, word);
//    return G;
//}
//
//int ladderLength(const string &beginWord, const string &endWord, const WordList &wordList) {
//    Dict dict;
//    copy(cbegin(wordList), cend(wordList), inserter(dict, begin(dict)));// Speed up Lookup with a hashset
//    auto G = makeAdjList(wordList, dict);                               // Create an Adjacency list of the graph. If we exceed memory or time, we can search each node live.
//    if (!dict.count(beginWord)) neighborSearch(dict, G, beginWord);     // If beginWord is not in the wordList, augment the graph with an additional node. Only need forward edges to the graph?
//    // Conduct a breadth first search until you find endWord, returning the depth of the word
//    auto depth = 0;
//    queue<string> q{{beginWord}};
//    set<string> visited;
//    while (!q.empty()) {
//        auto lvlSz = q.size();
//        while (lvlSz--) {
//            auto curr = q.front();
//            q.pop();
//            visited.insert(curr);// Mark Word as visited
//            if (curr == endWord) return depth + 1;
//            for (auto &w : as_const(G[curr])) {
//                if (!visited.count(w)) q.push(w);// Insert word if not visited
//            }
//        }
//        depth++;// Increment the depth
//    }
//    return 0;
//}
//
//
//TEST_CASE("127ex1", "[127]") {
//    auto beginWord = "hit";
//    auto endWord = "cog";
//    vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};
//    auto expected = 5;
//    REQUIRE(ladderLength(beginWord, endWord, wordList) == expected);
//}
//
//TEST_CASE("127ex2", "[127]") {
//    auto beginWord = "hit";
//    auto endWord = "cog";
//    vector<string> wordList{"hot", "dot", "dog", "lot"};
//    auto expected = 0;
//    REQUIRE(ladderLength(beginWord, endWord, wordList) == expected);
//}
//
//TEST_CASE("127ex3", "[127]") {
//    auto beginWord = "a";
//    auto endWord = "c";
//    vector<string> wordList{"a", "b", "c"};
//    auto expected = 2;
//    REQUIRE(ladderLength(beginWord, endWord, wordList) == expected);
//}