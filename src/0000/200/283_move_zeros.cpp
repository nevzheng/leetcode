// 283_move_zeros
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * The STL Solution would be
 * std::stable_partition(begin(nums), end(nums),
 * [](auto x){ x!=0;});
 *
 * Another Way of thinking about this problem is that 0s get bubbled up through
 * the array. We start at the beginning and keep a left and right pointer.
 * The left pointer indicates the last position in the transformed array
 * and the right pointer looks for non zero values
 */
class Solution {
 public:
  static void moveZeroes(vector<int>& nums) {
    auto r = 0UL;
    auto l = 0UL;
    while (r < nums.size()) {
      if (nums[r] != 0) std::swap(nums[l++], nums[r]);
      ++r;
    }
  }
};

TEST_CASE("283::1", "[283]") {
  vector<int> nums = {0, 1, 0, 3, 12};
  const vector<int> expected = {1, 3, 12, 0, 0};
  Solution::moveZeroes(nums);
  REQUIRE(nums == expected);
}

TEST_CASE("283::2", "[283]") {
  vector<int> nums = {0, 1, 0, 3, 12};
  const vector<int> expected = {1, 3, 12, 0, 0};
  Solution::moveZeroes(nums);
  REQUIRE(nums == expected);
}
