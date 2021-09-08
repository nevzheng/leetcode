// 784_letter_case_permutation
// Nevin Zheng
// 9/7/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static void dfs(string& s, int idx, vector<string>& ans) {
    if (idx == static_cast<int>(s.size())) return ans.push_back(s);
    // Stash original
    dfs(s, idx + 1, ans);  // Recurse w/ original char
    if (!isdigit(s[idx])) {
      s[idx] = islower(s[idx]) ? toupper(s[idx]) : tolower(s[idx]);
      dfs(s, idx + 1, ans);  // Recurse w/ swapped case
    }
  }

  static vector<string> letterCasePermutation(string s) {
    vector<string> ans;
    dfs(s, 0, ans);
    return ans;
  }
};

TEST_CASE("784::1", "[784]") {
  const string input = "a1b2";
  vector<string> expected = {"a1b2", "a1B2", "A1b2", "A1B2"};
  REQUIRE(Solution::letterCasePermutation(input) == expected);
}