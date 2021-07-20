// 427concatenated_words
// Nevin Zheng
// 7/19/21

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <unordered_set>

using namespace std;

bool checkConcatenated(const unordered_set<string> &dict, const string &word, const int idx) {
    if (idx == word.size()) return true;// Reached the end
    string s;
    for (auto i = idx; i < word.size(); i++) {
        s += word[i];
        if (dict.count(s) && checkConcatenated(dict, word, i + 1)) return true;
    }
    return false;
}

/**
 * First we sort the word list by length. in O(n lg n) time and O(1) space
 * We will also use a hashset as a dictionary to store and query membership.
 * Concacenated words MUST be longer than any of their components
 * Processing shorter then longer ensures we will not miss any suffixes
 * If you convert the list to a dict at the beginning, you would need special
 * logic to identify concatenated words. false positives are triggered
 *
 * TLDR: SORT from shortest to longest lengths. this makes sure that components
 * are in the dict prior to concatenated words
 * then do a dfs.
 * @param words
 * @return
 */
vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
    // Process words from shortest to longest
    sort(begin(words), end(words),
         [](const auto &a, const auto &b) { return a.size() < b.size(); });
    unordered_set<string> dict;
    vector<string> ans;
    for (auto &w : as_const(words)) {
        if (w.empty()) continue;
        if (checkConcatenated(dict, w, 0)) ans.push_back(w);
        dict.insert(w);
    }
    return ans;
}

TEST_CASE("427ex1", "[427]") {
    vector<string> words = {"cat", "cats", "catsdogcats", "dog", "dogcatsdog", "hippopotamuses", "rat", "ratcatdogcat"};
    vector<string> expected = {"catsdogcats", "dogcatsdog", "ratcatdogcat"};
    REQUIRE(findAllConcatenatedWordsInADict(words) == expected);
}