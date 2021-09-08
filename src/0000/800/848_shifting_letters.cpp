// 848_shifting_letters
// Nevin Zheng
// 9/8/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * First we will compute the total number of shifts for each character.
 * Each index is shifted by shifts succeeding it. Thus we can compute the
 * total shift for each index with a reverse prefix sum implemented by
 * inclusive scan with reverse iterators.
 * We also need to avoid overflow so we will be taking module 26, the length of
 * the alphabet.
 * Then we can apply a transform to compute the result applying the total shifts
 */
class Solution {
 public:
  static const int kAlphabetSize = 26;
  static string shiftingLetters(string s, const vector<int>& shifts) {
    vector<int> total_shifts(s.size());
    std::inclusive_scan(
        crbegin(shifts), crend(shifts), rbegin(total_shifts),
        [](int pre, int sh) {
          return ((pre % kAlphabetSize) + (sh % kAlphabetSize)) % kAlphabetSize;
        });
    std::transform(begin(s), end(s), begin(total_shifts), begin(s),
                   [](char c, int sh) {
                     return (((c - 'a') + sh) % kAlphabetSize) + 'a';
                   });
    return s;
  }
};

TEST_CASE("848::1", "[848]") {
  const string s = "abc";
  const vector<int> shifts{3, 5, 9};
  const string expected = "rpl";
  REQUIRE(Solution::shiftingLetters(s, shifts) == expected);
}

TEST_CASE("848::2", "[848]") {
  const string s = "aaa";
  const vector<int> shifts{1, 2, 3};
  const string expected = "gfd";
  REQUIRE(Solution::shiftingLetters(s, shifts) == expected);
}