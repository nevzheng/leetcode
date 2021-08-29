// 977_squares_of_a_sorted_array
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * A Naive Approach is square and then sort the numbers
 * This takes O(nlgn) time and O(1) space
 * A better approach is a two pointer technique. We init two pointers at
 * the beginning and end of the array.
 * Then fill an answer array with the largest square adjusting the two
 * pointers as we progress.
 */
class Solution {
 public:
  static vector<int> sortedSquares(const vector<int>& nums) {
    vector<int> ans(nums.size());
    auto l = 0UL;
    auto r = nums.size() - 1;
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
      auto lsq = nums[l] * nums[l];
      auto rsq = nums[r] * nums[r];
      if (lsq < rsq) {
        *it = rsq;
        --r;
      } else {
        *it = lsq;
        ++l;
      }
    }
    return ans;
  }
};

TEST_CASE("977::1", "[977]") {
  const vector<int> nums{-4, -1, 0, 3, 10};
  const vector<int> expected{0, 1, 9, 16, 100};
  REQUIRE(Solution::sortedSquares(nums) == expected);
}

TEST_CASE("977::2", "[977]") {
  const vector<int> nums{-7, -3, 2, 3, 11};
  const vector<int> expected{4, 9, 9, 49, 121};
  REQUIRE(Solution::sortedSquares(nums) == expected);
}
