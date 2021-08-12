// 49_group_anagrams
// Nevin Zheng
// 8/12/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static vector<vector<string>> groupAnagrams(const vector<string>& strs) {
    map<string, vector<string>> anagrams;
    for (const auto& s : strs) {
      auto k = s;
      std::sort(k.begin(), k.end());
      anagrams[k].push_back(s);
    }
    vector<vector<string>> ans;
    std::transform(anagrams.begin(), anagrams.end(), back_inserter(ans),
                   [](const auto kv) { return kv.second; });
    return ans;
  }
};

TEST_CASE("49::1", "[49]") {
  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
  vector<vector<string>> expected = {
      {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};

  REQUIRE(Solution::groupAnagrams(strs) == expected);
}