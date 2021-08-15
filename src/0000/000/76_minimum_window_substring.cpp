// 76_minimum_window_substring
// Nevin Zheng
// 8/15/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We apply a sliding window technique. we maintain a set of char counts int
 * the window and compare them to counts of chars in t. If the number of unique
 * chars and their counts match, we can record the string
 * when the condition is met, we can then attempt to shrink the best string
 * by incrementing the left boundary and removing chars until the condition is
 * no longer met
 * Time: O(M+N)
 * Space: 2 vectors of size 256: Constant
 */
class Solution {
 public:
  static string minWindow(const string& s, const string& t) {
    if (s.empty() or t.empty()) return "";
    const int k_ascii_size = 256;
    vector<int> tc(k_ascii_size);  // Char counts in t
    vector<int> wc(k_ascii_size);  // Char counts in curr window
    for (auto x : t) ++tc[x];
    auto required =
        std::count_if(tc.cbegin(), tc.cend(), [](auto x) { return x != 0; });
    auto met = 0L;  // num of required chars in window
    auto r = 0UL;
    auto l = 0UL;
    auto best_l = 0UL;
    auto best_len = UINT64_MAX;
    while (r < s.size()) {
      auto cur = s[r];
      ++wc[cur];                                  // Add r to window
      if (tc[cur] and wc[cur] == tc[cur]) ++met;  // Increment met if valid
      // Shrink window to search for shorter strings
      while (met == required and l <= r) {
        cur = s[l];
        if (r - l + 1 < best_len) {
          best_l = l;
          best_len = r - l + 1;
        }
        --wc[cur];                                 // Pop l from set
        if (tc[cur] and wc[cur] < tc[cur]) --met;  // Remove from met
        ++l;                                       // Increment l
      }
      ++r;  // increment r
    }
    return best_len != UINT64_MAX ? s.substr(best_l, best_len) : "";
  }
};

TEST_CASE("76::1", "[76]") {
  const auto s = "ADOBECODEBANC"s;
  const auto t = "ABC"s;
  auto expected = "BANC"s;
  REQUIRE(Solution::minWindow(s, t) == expected);
}

TEST_CASE("76::2", "[76]") {
  const auto s = "a"s;
  const auto t = "a"s;
  auto expected = "a"s;
  REQUIRE(Solution::minWindow(s, t) == expected);
}

TEST_CASE("76::3", "[76]") {
  const auto s = "a"s;
  const auto t = "aa"s;
  auto expected = ""s;
  REQUIRE(Solution::minWindow(s, t) == expected);
}