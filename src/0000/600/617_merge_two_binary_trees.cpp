// 617_merge_two_binary_trees
// Nevin Zheng
// 9/4/21

#include "Tree.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  TreeNode* mergeTrees(TreeNode* x, TreeNode* y) {
    if (x && y) {
      auto* root = new TreeNode(x->val + y->val);
      root->left = mergeTrees(x->left, y->left);
      root->right = mergeTrees(x->right, y->right);
      return root;
    }
    return x ? x : y;
  }
};