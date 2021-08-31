// 598_range_addition_2
// Nevin Zheng
// 8/30/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * One naive strategy would be to instantiate a mxn matrix and apply all the
 * operations. This is inefficient.
 *
 * A square (x,y) is only incremented if its in a given input (p,q).
 * Each rectangle created p,q starts at 0,0.
 * We need to find the rectangle that overlaps with the most squares.
 * and find its product.
 * This is equivalent to finding the minimum m and minimum n values in all the
 * ops.
 *
 */
class Solution {
 public:
  static int maxCount(int m, int n, const vector<vector<int>>& ops) {
    if (ops.empty()) return m * n;
    for (const auto& op : ops) {
      m = std::min(m, op.front());
      n = std::min(n, op.back());
    }
    return m * n;
  }
};

TEST_CASE("598::1", "[98]") {
  auto m = 3;
  auto n = 3;
  vector<vector<int>> ops{{2, 2}, {3, 3}};
  auto expected = 4;
  REQUIRE(Solution::maxCount(m, n, ops) == expected);
}

TEST_CASE("598::2", "[98]") {
  auto m = 3;
  auto n = 3;
  vector<vector<int>> ops{{2, 2}, {3, 3}, {3, 3}, {3, 3}, {2, 2}, {3, 3},
                          {3, 3}, {3, 3}, {2, 2}, {3, 3}, {3, 3}, {3, 3}};
  auto expected = 4;
  REQUIRE(Solution::maxCount(m, n, ops) == expected);
}

TEST_CASE("598::3", "[98]") {
  auto m = 3;
  auto n = 3;
  vector<vector<int>> ops;
  auto expected = 9;
  REQUIRE(Solution::maxCount(m, n, ops) == expected);
}

TEST_CASE("598::4", "[98]") {
  auto m = 39999;
  auto n = 39999;
  vector<vector<int>> ops{{19999, 19999}};
  auto expected = 19999 * 19999;
  REQUIRE(Solution::maxCount(m, n, ops) == expected);
}
