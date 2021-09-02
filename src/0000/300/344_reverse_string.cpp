// 344_reverse_string
// Nevin Zheng
// 8/31/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  void reverseString(vector<char>& s) {
    auto l = 0UL;
    auto r = s.size() - 1;
    while (l < r) std::swap(s[l++], s[r--]);
  }
};