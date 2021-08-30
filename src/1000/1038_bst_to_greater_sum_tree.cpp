// 1038_bst_to_greater_sum_tree
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

/**
 * Imagine we perform a Reverse Inorder Traversal, Processing RIGHT, SELF, and
 * than LEFT.
 * We maintain an accumulator variable that will track the sum of nodes
 * traversed. Updating Nodes as we traverse the trees, and returning the total
 *
 */
class Solution {
 public:
  static int dfs(TreeNode* root, int total) {
    if (!root) return total;
    root->val += dfs(root->right, total);
    return dfs(root->left, root->val);
  }

  static TreeNode* bstToGst(TreeNode* root) {
    dfs(root, 0);
    return root;
  }
};

TEST_CASE("1038::1", "[1038]") {
  auto eight = make_unique<TreeNode>(8);
  auto five = make_unique<TreeNode>(5);
  auto seven = make_unique<TreeNode>(7, nullptr, eight.get());
  auto six = make_unique<TreeNode>(6, five.get(), seven.get());
  auto three = make_unique<TreeNode>(3);
  auto two = make_unique<TreeNode>(2, nullptr, three.get());
  auto zero = make_unique<TreeNode>(0);
  auto one = make_unique<TreeNode>(1, zero.get(), two.get());
  auto four = make_unique<TreeNode>(4, one.get(), six.get());
  REQUIRE(Solution::bstToGst(four.get()) != nullptr);
}
