// 108_convert_sorted_array_to_binary_search_tree
// Nevin Zheng
// 7/26/21

#include "Tree.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We are given a sorted list. A balanced tree has roughly an equal amount
 * of elements in each sub tree.
 * The array is sorted so we can split the tree at the median/middle
 * and recurse. We should end up with a height balanced tree
 * @param nums
 * @return
 */
TreeNode* sortedArrayToBST(const vector<int>& nums) {
  if (nums.empty()) return nullptr;
  auto len = static_cast<int>(nums.size());
  if (len == 1) return new TreeNode(nums.front());
  auto mid = len / 2;
  auto* root = new TreeNode(nums[mid]);
  auto mid_it = begin(nums) + mid;

  vector left(begin(nums), mid_it);
  vector right(mid_it + 1, end(nums));

  root->left = sortedArrayToBST(left);
  root->right = sortedArrayToBST(right);

  return root;
}

TEST_CASE("108ex1", "[108]") {
  const vector<int> nums = {-10, -3, 0, 5, 9};
  auto* result = sortedArrayToBST(nums);
  REQUIRE(result != nullptr);
}