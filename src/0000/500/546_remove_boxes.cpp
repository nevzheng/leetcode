// 546_remove_boxes
// Nevin Zheng
// 8/14/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 *  A naive approach would be to do backtracking simulating the process
 *  and all possible outcomes. The worst case occurs if the all elements
 *  are unique and different. the constraint specifies a max len of 100
 *  thus in the worst case we get a complexity of O(100^100) which is terrible
 *  We're going to need a better solution
 *
 * Another thought would be a greedy approach where we take the longest
 * contiguous array at each step. The first example given eliminates this
 * possibility. It produces the incorrect answer.
 *
 * It looks like we're going to have to apply dynamic programming.
 * https://leetcode.com/problems/remove-boxes/discuss/1402561/Python-Top-down-DP-Clear-explanation-with-Picture-Clean-and-Concise
 * https://leetcode.com/problems/remove-boxes/discuss/1403059/Easy-to-Understand-or-C%2B%2B-or-DP-or-Top-Down
 */
class Solution {
 public:
  int dp_[101][101][101];

  int solve(const vector<int>& boxes, int l, int r, int k) {
    if (l > r) return 0;
    if (dp_[l][r][k] != -1) return dp_[l][r][k];
    auto ans = solve(boxes, l + 1, r, 0) + (k + 1) * (k + 1);
    for (auto j = l + 1; j < r + 1; ++j)
      if (boxes[l] == boxes[j]) {
        ans =
            max(ans, solve(boxes, j, r, k + 1) + solve(boxes, l + 1, j - 1, 0));
      }
    return dp_[l][r][k] = ans;
  }

  int removeBoxes(const vector<int>& boxes) {
    memset(dp_, -1, sizeof(dp_));
    return solve(boxes, 0, boxes.size() - 1, 0);
  }
};

TEST_CASE("546::1", "[546]") {
  vector<int> boxes{1, 3, 2, 2, 2, 3, 4, 3, 1};
  const auto expected = 23;
  REQUIRE(Solution().removeBoxes(boxes) == expected);
}

TEST_CASE("546::2", "[546]") {
  vector<int> boxes{1, 1, 1};
  const auto expected = 9;
  REQUIRE(Solution().removeBoxes(boxes) == expected);
}

TEST_CASE("546::3", "[546]") {
  vector<int> boxes{1};
  const auto expected = 1;
  REQUIRE(Solution().removeBoxes(boxes) == expected);
}