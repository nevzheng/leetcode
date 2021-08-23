// 653_two_sum_iv
// Nevin Zheng
// 8/23/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <Tree.hpp>

using namespace std;

/**
 * There are a few approaches that we can take.
 *
 * Firstly we can use an inorder traversal to flatten the array then
 * perform the two ptr technique from the original two sum.
 * This will take O(n) time and O(n) space.
 *
 * Secondly we can traverse the tree in order, and search for the complement
 * tgt-x. There are n nodes and we'll need to perform a lgn search for each
 * we'll also need lg n stack space.
 * Overall O(n lgn) time and lg(n) space. Tree could be degenerate so space
 * could be n.
 *
 * Thirdly we can adapt the two ptr technique for trees. We will have
 * two iterators. one will be an increasing inorder traversal. the other will be
 * a decreasing, reverse in order traversal. We can then apply the two ptr
 * technique
 * This will take O(n) time and O(lgn) space.
 *
 * The third approach is the most optimal, however, the first approach is the
 * easiest to implement. So we'll go with the first one and then circle back
 * to the third.
 */
// class SolutionFlatten {
//  public:
//   void inorder_traversal(TreeNode* root, vector<int>& nums) {
//     if (!root) return;
//     if (root->left) inorder_traversal(root->left, nums);
//     nums.push_back(root->val);
//     if (root->right) inorder_traversal(root->right, nums);
//   }
//
//   static bool two_sum(const vector<int>& nums, int k) {
//     auto lt = nums.begin();
//     auto rt = prev(nums.end());
//     while (lt < rt) {
//       auto sum = *lt + *rt;
//       if (sum == k) return true;
//       sum < k ? ++lt : --rt;
//     }
//     return false;
//   }
//
//   bool findTarget(TreeNode* root, int k) {
//     vector<int> nums;
//     inorder_traversal(root, nums);  // Flatten BST inorder, ascending order
//     return two_sum(nums, k);
//   }
// };

/**
 * In this solution we will use a hash map to traverse the tree and record
 * values we see. at each node we will check the hash map to see if the
 * complement exists. If it does we'll return true, else we keep searching
 *
 * Worst Case: O(n) time and O(n) space for the stack
 * If the tree is balanced we'll use at most O(h = lgn) space
 */
class Solution {
 public:
  unordered_set<int> seen_;

  bool findTarget(TreeNode* root, int k) {
    if (!root) return false;
    if (root->left && findTarget(root->left, k)) return true;
    if (seen_.count(k - root->val) != 0) return true;
    seen_.insert(root->val);
    if (root->right && findTarget(root->right, k)) return true;
    return false;
  }
};

TEST_CASE("553::1", "[553]") {
  auto seven = make_unique<TreeNode>(7);
  auto four = make_unique<TreeNode>(4);
  auto two = make_unique<TreeNode>(2);
  auto six = make_unique<TreeNode>(6, nullptr, seven.get());
  auto three = make_unique<TreeNode>(3, two.get(), four.get());
  auto five = make_unique<TreeNode>(5, three.get(), six.get());
  const auto k = 9;
  auto expected = true;
  REQUIRE(Solution().findTarget(five.get(), k) == expected);
}

TEST_CASE("553::2", "[553]") {
  auto seven = make_unique<TreeNode>(7);
  auto four = make_unique<TreeNode>(4);
  auto two = make_unique<TreeNode>(2);
  auto six = make_unique<TreeNode>(6, nullptr, seven.get());
  auto three = make_unique<TreeNode>(3, two.get(), four.get());
  auto five = make_unique<TreeNode>(5, three.get(), six.get());
  const auto k = 28;
  auto expected = false;
  REQUIRE(Solution().findTarget(five.get(), k) == expected);
}