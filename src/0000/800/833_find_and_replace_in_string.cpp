// 833_find_and_replace_in_string
// Nevin Zheng
// 8/16/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We first find the len of the final string
 * then resize the string to old len + new len
 * we then start processing the string by using a two pointer approach t
 */
class Solution {
 public:
  static string findReplaceString(string& s, const vector<int>& indices,
                                  const vector<string>& sources,
                                  const vector<string>& targets) {
    // Compute The Size of the final string
    auto len = s.size();
    auto new_len = s.size();
    for (auto i = 0UL; i < indices.size(); ++i) {
      if (s.compare(indices[i], sources[i].size(), sources[i]) == 0)
        new_len = new_len - sources[i].size() + targets[i].size();
    }
    s.resize(len + new_len);  // Resize to len + new_len; O(N) time
    auto wr = len;            // Set Write Cursor to len+1
    auto rd = 0UL;            // Read cursor
    while (rd < len) {
      auto it = std::find(indices.begin(), indices.end(), rd);  // O(kN)
      if (it == indices.end()) continue;
      auto idx = distance(indices.begin(), it);
      auto so_sz = sources[idx].size();
      if (s.compare(rd, so_sz, sources[idx]) == 0) {
        for (auto c : targets[idx]) s[wr++] = c;
        rd += so_sz;  // Advance
      } else {
        s[wr++] = s[rd++];  // Copy over if no replace
      }
    }
    std::rotate(s.begin(), std::next(s.begin(), len), s.end());  // O(N)
    s.resize(new_len);
    return s;
  }
};

TEST_CASE("833::1", "[833]") {
  string s = "abcd";
  const vector<int> indices{0, 2};
  const vector<string> sources{"a", "cd"};
  const vector<string> targets = {"eee", "ffff"};
  const string expected = "eeebffff";
  REQUIRE(Solution::findReplaceString(s, indices, sources, targets) ==
          expected);
}

TEST_CASE("833::2", "[833]") {
  string s = "abcd";
  const vector<int> indices{0, 2};
  const vector<string> sources{"ab", "ec"};
  const vector<string> targets = {"eee", "ffff"};
  const string expected = "eeecd";
  REQUIRE(Solution::findReplaceString(s, indices, sources, targets) ==
          expected);
}