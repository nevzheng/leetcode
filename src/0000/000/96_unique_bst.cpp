// 96_unique_bst
// Nevin Zheng
// 8/16/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * Given an array [1,2,3,4], there are four possible choices for the root
 * [| 1 | ,2,3,4]  + [ 1, | 2 |, 3, 4] | [1,2|3|, 4] and [1,2,3|4|]
 * for [| 1 | ,2,3,4], we can multiply the num of ways to arrange the left and
 * right sub trees to get the result of that choice of root
 * the num of ways to do a subtree is just applying numTrees again.
 * The number of unique trees is thus the sum of all the ways
 * This is confusing but is better if you draw a diagram
 *
 * this is also the nth catalan number. there are several ways of computing it
 * but i will use dynamic programming.
 *
 */
class Solution {
 public:
  int numTrees(int n) {
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (auto i = 1; i <= n; ++i) {
      for (auto j = 0; j < i; ++j) {
        dp[i] += dp[j] * dp[i - j - 1];
      }
    }
    return dp.back()
  }
};
