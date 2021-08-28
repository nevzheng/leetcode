// 522_longest_uncommon_subsequence_2
// Nevin Zheng
// 8/27/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static bool isSubsequence(string a, string b) {
    auto i = 0UL, j = 0UL;
    while (i < a.length() && j < b.length()) {
      if (a[i] == b[j]) j++;
      i++;
    }
    return j == b.length();
  }

  static int findLUSlength(vector<string>& strs) {
    // Sort In Decreasing Order
    std::sort(strs.begin(), strs.end(),
              [](const auto& a, const auto& b) { return a.size() > b.size(); });
    set<string> duplicates = getDuplicates(strs);
    for (auto i = 0UL; i < strs.size(); ++i) {
      if (!duplicates.count(strs[i])) {
        // Unique Longest String, can't be subsequence of other strs
        if (i == 0) return static_cast<int>(strs[i].size());
        // Not Longest, check if it is a subseq of other strs
        for (auto j = 0UL; j < i; ++j) {
          if (isSubsequence(strs[j], strs[i])) break;
          if (j == i - 1) return static_cast<int>(strs[i].size());
        }
      }
    }
    return -1;
  }
  static set<string> getDuplicates(vector<string>& strs) {
    map<string, int> count;
    for (const auto& s : strs) ++count[s];
    set<string> duplicates;
    // Create a set of duplicates
    copy_if(strs.cbegin(), strs.cend(), inserter(duplicates, begin(duplicates)),
            [&count](const auto& s) { return count[s] > 1; });
    return duplicates;
  }
};

TEST_CASE("522::1", "[5222]") {
  vector<string> strs = {"aba", "cdc", "eae"};
  auto expected = 3;
  REQUIRE(Solution::findLUSlength(strs) == expected);
}

TEST_CASE("522::2", "[5222]") {
  vector<string> strs = {"aaa", "aaa", "aa"};
  auto expected = -1;
  REQUIRE(Solution::findLUSlength(strs) == expected);
}