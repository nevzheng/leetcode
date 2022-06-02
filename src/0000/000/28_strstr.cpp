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
 * This implementation of strStr uses KMP and runs in O(m+n) time and O(n)
 * space. Where m is the size of the haystack and n the size of the needle
 */
class KMPSolution {
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

/**
 * This implementation of strStr uses Rabin Karp
 */
class Solution {
 public:
  static int strStr(string haystack, string needle) {
    // Base cases
    auto h_len = haystack.length();
    auto m_len = needle.length();
    if (m_len == 0) return 0;
    if (h_len == 0 || h_len < m_len) return -1;

    // Hashing:
    // or using fast integer power algo:
    // radix^(m - 1) % prime: int h = pow(d, m - 1) % q;
    const int d = 31;        // radix - beneficial to make smaller
    const int q = 15486703;  // some big prime
    auto p = 0L;
    auto t = 0L;
    auto h = 1L;
    // preprocessing hashes for pattern and text
    for (auto i = 0UL; i < m_len; ++i) {
      if (i != m_len - 1) h = (d * h) % q;
      p = (d * p + needle[i]) % q;
      t = (d * t + haystack[i]) % q;
    }
    for (auto s = 0UL; s < h_len - m_len + 1; ++s) {
      if (t < 0) t += q;  // fix negative hash
      // Match, Check String
      if (p == t and haystack.compare(s, m_len, needle) == 0) return s;
      // updating hash: pop front char, push new
      if (s < h_len - m_len) t = (d * (t - haystack[s] * h) + haystack[s + m_len]) % q;
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

TEST_CASE("28::4", "[28]") {
  string haystack = "aaa";
  string needle = "aaaa";
  auto expected = -1;
  REQUIRE(Solution::strStr(haystack, needle) == expected);
}

TEST_CASE("28::5", "[28]") {
  string haystack = "";
  string needle = "a";
  auto expected = -1;
  REQUIRE(Solution::strStr(haystack, needle) == expected);
}

TEST_CASE("28::6", "[28]") {
  string haystack = "a";
  string needle = "a";
  auto expected = 0;
  REQUIRE(Solution::strStr(haystack, needle) == expected);
}