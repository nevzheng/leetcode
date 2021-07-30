// 124_binary_tree_max_path_value
// Nevin Zheng
// 7/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

class Solution {
  int max_path_ = INT_MIN;

  int dfs(TreeNode* root) {
    if (!root) return 0;
    auto l_path = dfs(root->left);
    auto r_path = dfs(root->right);
    // From left through node down to right.
    auto subtree_path = root->val + l_path + r_path;
    max_path_ = max(max_path_, subtree_path);
    // On the way up to root
    l_path = max(0, l_path);
    r_path = max(0, r_path);
    auto through_path = root->val + max(l_path, r_path);
    max_path_ = max(max_path_, through_path);

    return through_path;
  }

 public:
  int maxPathSum(TreeNode* root) {
    dfs(root);
    return max_path_;
  }
};

TEST_CASE("124ex1", "[124]") {
  auto* two = new TreeNode(2);
  auto* three = new TreeNode(3);
  auto* root = new TreeNode(1, two, three);
  auto expected = 6;
  REQUIRE(Solution().maxPathSum(root) == expected);
}

TEST_CASE("124ex2", "[124]") {
  auto* nine = new TreeNode(9);
  auto* fifteen = new TreeNode(15);
  auto* seven = new TreeNode(7);
  auto* twenty = new TreeNode(20, fifteen, seven);
  auto* root = new TreeNode(-10, nine, twenty);
  auto expected = 42;
  REQUIRE(Solution().maxPathSum(root) == expected);
}

TEST_CASE("124ex3", "[124]") {
  auto* root = new TreeNode(-3);
  auto expected = -3;
  REQUIRE(Solution().maxPathSum(root) == expected);
}

TEST_CASE("124ex4", "[124]") {
  auto* neg_one = new TreeNode(-1);
  auto* neg_two = new TreeNode(-2);
  auto* root = new TreeNode(2, neg_one, neg_two);
  auto expected = 2;
  REQUIRE(Solution().maxPathSum(root) == expected);
}