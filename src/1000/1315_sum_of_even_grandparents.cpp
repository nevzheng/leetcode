// 1315_sum_of_even_grandparents
// Nevin Zheng
// 8/3/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

class Solution {
 public:
  int gp_sum_;
  void dfs(TreeNode* root, TreeNode* parent, TreeNode* gp) {
    if (!root) return;
    if (gp and gp->val % 2 == 0) gp_sum_ += root->val;
    if (root->left) dfs(root->left, root, parent);
    if (root->right) dfs(root->right, root, parent);
  }

  int sumEvenGrandparent(TreeNode* root) {
    dfs(root, nullptr, nullptr);
    return gp_sum_;
  }
};