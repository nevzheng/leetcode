// 189_rotate_array
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * There are a few ways to rotate an array
 * The easiest one to remember is that either a left
 * or right rotation can be composed of applications
 * of the reverse function.
 *
 * There's also a std::rotate function
 *
 * EX: Rotate by 3 left
 * [1,2,3,4,5,6] // Original
 * [3,2,1,| 6,5,4] // Reverse Segments
 * [4,5,6,1,2,3] // Reverse whole Array
 *
 *
 * EX Rotate by 3 RIGHT
 * [1,2,3,4,5,6] // Original
 * [6,5,4,3,2,1] // Reverse Whole
 * [4,5,6,1,2,3] // Reverse Segments
 */
class Solution {
 public:
  static void rotate(vector<int>& nums, int k) {
    if (k == 0) return;
    k %= static_cast<int>(nums.size());       // Make Sure its in range
    std::reverse(nums.begin(), nums.end());   // Reverse Whole
    reverse(nums.begin(), nums.begin() + k);  // Reverse First Seg
    reverse(nums.begin() + k, nums.end());    // Reverse Second Seg
  }
};

TEST_CASE("189::1", "[189]") {
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
  const auto k = 3;
  const vector<int> expected = {5, 6, 7, 1, 2, 3, 4};
  Solution::rotate(nums, k);
  REQUIRE(nums == expected);
}

TEST_CASE("189::2", "[189]") {
  vector<int> nums = {-1, -100, 3, 99};
  const auto k = 2;
  const vector<int> expected = {3, 99, -1, -100};
  Solution::rotate(nums, k);
  REQUIRE(nums == expected);
}