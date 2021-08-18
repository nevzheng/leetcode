// 639_decode_ways_2
// Nevin Zheng
// 8/18/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
  - public:int numDecodings(const string& s) {
    const int mod = 1e9 + 7;
    const int k1x = 9;
    const int k2x = 6;
    int64_t first = 1;
    int64_t second = [&]() {
      if (s[0] == '*') return k1x;
      if (s[0] == '0') return 0;
      return 1;
    }();

    for (int i = 1UL; i < s.length(); i++) {
      // Save for next iteration
      int64_t tmp = second;
      if (s[i] == '*') {
        // Account for 1-9
        second = k1x * second % mod;
        if (s[i - 1] == '1') {
          second = (second + k1x * first) % mod;
        } else if (s[i - 1] == '2') {
          second = (second + k2x * first) % mod;
        } else if (s[i - 1] == '*') {
          second = (second + (k1x + k2x) * first) % mod;
        }
      } else {
        second = s[i] == '0' ? 0 : second;
        if ((s[i - 1] == '1') || (s[i - 1] == '2' && s[i] <= '6')) {
          second = (second + first) % mod;
        } else if (s[i - 1] == '*') {
          auto x = s[i] <= '6' ? 2 : 1;
          second = (second + x * first) % mod;
        }
      }
      first = tmp;  // Shift for next iter
    }
    return second;
  }
};