// 242_valid_anagram
// Nevin Zheng
// 8/16/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  bool isAnagram(string s, string t) {
    sort(begin(s), end(s));
    sort(begin(t), end(t));
    return s == t;
  }
};

// class Solution {
//  public:
//   bool isAnagram(const string& s, const string& t) {
//     map<char, int> sm;
//     map<char, int> tm;
//     for (auto c : s) ++sm[c];
//     for (auto c : t) ++tm[c];
//     return sm == tm;
//   }
// };
