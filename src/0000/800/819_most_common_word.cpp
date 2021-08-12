// 819_most_common_word
// Nevin Zheng
// 8/10/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static string mostCommonWord(string& paragraph,
                               const vector<string>& banned) {
    unordered_set<string> banned_dict(banned.begin(), banned.end());
    std::transform(
        paragraph.begin(), paragraph.end(), begin(paragraph),
        [](const auto& c) { return tolower(c); });  // Covert to lowercase
    // Replace Punctuation with whitespace. punctuation has meaning
    std::replace_if(paragraph.begin(), paragraph.end(), ::ispunct, ' ');
    // Split into words
    istringstream iss(paragraph);
    vector<string> words{istream_iterator<string>{iss},
                         istream_iterator<string>()};
    map<string, int> freq;
    for (auto& w : words) {
      if (!banned_dict.count(w)) ++freq[w];
    }
    return std::max_element(
               freq.begin(), freq.end(),
               [](const auto& x, const auto& y) { return x.second < y.second; })
        ->first;
  }
};

TEST_CASE("819ex1", "[819]") {
  string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
  vector<string> banned = {"hit"};
  string expected = "ball";
  REQUIRE(Solution::mostCommonWord(paragraph, banned) == expected);
}

TEST_CASE("819ex2", "[819]") {
  string paragraph = "a, a, a, a, b,b,b,c, c";
  vector<string> banned = {"a"};
  string expected = "b";
  REQUIRE(Solution::mostCommonWord(paragraph, banned) == expected);
}