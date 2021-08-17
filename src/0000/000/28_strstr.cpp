// 28_strstr
// Nevin Zheng
// 8/17/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * This Version of strstr take O(N^2) time and constant space
 */
// class Solution {
//  public:
//   static int strStr(const string& haystack, const string& needle) {
//     if (needle.empty()) return 0;
//     auto n = 0UL;                                   // Needle Index
//     for (auto h = 0UL; h < haystack.size(); ++h) {  // haystack index
//       if (haystack[h] == needle[n]) {
//         ++n;
//       } else {
//         h = h - n;  // Skip Ahead by amount of mismatch
//         n = 0;      // reset needle index
//       }
//       if (n == needle.size()) {
//         return h - n + 1;
//       }
//     }
//     return -1;
//   }
// };

/**
 * This implmentation of strStr uses KMP and runs in O(m+n) time and O(n) space.
 * Where m is the size of the haystack and n the size of the needle
 */
class Solution {
 public:
  static vector<int> computeLPS(const string& w) {
    auto size = static_cast<int>(w.size());
    vector<int> lps(size);
    lps[0] = 0;
    auto i = 0;
    auto j = 1;
    while (j < size) {
      if (w[j] == w[i]) {
        lps[j++] = ++i;
      } else {
        if (i != 0) {
          i = lps[i - 1];
        } else {
          lps[j++] = 0;
        }
      }
    }
    return lps;
  }

  static int strStr(const string& haystack, const string& needle) {
    if (needle.empty()) return 0;
    auto M = haystack.size();
    auto N = needle.size();
    auto lps = computeLPS(needle);

    auto h = 0UL;
    auto n = 0UL;

    while (h < M) {
      if (haystack[h] == needle[n]) ++h, ++n;  // Increment both indices
      if (n == N) return h - n;                // return first occurence
      if (n < N && needle[n] != haystack[h]) {
        if (n != 0)
          n = lps[n - 1];
        else
          ++h;
      }
    }
    return -1;
  }
};

TEST_CASE("28::1", "[28]") {
  string haystack = "hello";
  string needle = "ll";
  auto expected = 2;
  REQUIRE(Solution::strStr(haystack, needle) == expected);
}

TEST_CASE("28::2", "[28]") {
  string haystack = "aaaaa";
  string needle = "bba";
  auto expected = -1;
  REQUIRE(Solution::strStr(haystack, needle) == expected);
}

TEST_CASE("28::3", "[28]") {
  string haystack;
  string needle;
  auto expected = 0;
  REQUIRE(Solution::strStr(haystack, needle) == expected);
}