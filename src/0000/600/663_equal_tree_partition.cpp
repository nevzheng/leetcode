// 663_equal_tree_partition
// Nevin Zheng
// 8/29/21
// https://www.cnblogs.com/grandyang/p/7550360.html

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

/**
 * We First determine the sums of all possible subtrees and store them in the
 * array then given the sum of the entire tree we can DFS the tree
 * checking if cutting an edge will result in equal parts
 */
class Solution {
 public:
  map<TreeNode*, int> cache_;
  int tree_sum(TreeNode* root) {
    if (!root) return 0;
    if (auto it = cache_.find(root); it != cache_.end()) return it->second;
    int l_sum = root->left ? tree_sum(root->left) : 0;
    int r_sum = root->right ? tree_sum(root->right) : 0;
    return cache_[root] = root->val + l_sum + r_sum;
  }

  bool dfs(TreeNode* root, int total) {
    if (!root) return false;
    return (tree_sum(root->left) == total / 2) ||
           (tree_sum(root->right) == total / 2) || dfs(root->left, total) ||
           dfs(root->right, total);
  }

  bool checkEqualTree(TreeNode* root) {
    auto total = tree_sum(root);
    return dfs(root, total);
  }
};

TEST_CASE("663:1", "[663]") {
  auto three = make_unique<TreeNode>(3);
  auto two = make_unique<TreeNode>(2);
  auto ten2 = make_unique<TreeNode>(10, two.get(), three.get());
  auto ten1 = make_unique<TreeNode>(10);
  auto five = make_unique<TreeNode>(5, ten1.get(), ten2.get());
  auto expected = true;
  REQUIRE(Solution().checkEqualTree(five.get()) == expected);
}

TEST_CASE("663:2", "[663]") {
  auto two2 = make_unique<TreeNode>(2);
  auto twenty = make_unique<TreeNode>(20);
  auto ten1 = make_unique<TreeNode>(2, two2.get(), twenty.get());
  auto two1 = make_unique<TreeNode>(2);
  auto one = make_unique<TreeNode>(1, two1.get(), ten1.get());
  auto expected = false;
  REQUIRE(Solution().checkEqualTree(one.get()) == expected);
}
