// 404_sum_of_left_leaves
// Nevin Zheng
// 8/14/21

#include "Tree.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
using namespace std;

class Solution {
 public:
  static void dfs(TreeNode* root, bool is_left, int& sum) {
    if (!root) return;
    if (is_left and !root->left and !root->right) sum += root->val;
    if (root->left) dfs(root->left, true, sum);
    if (root->right) dfs(root->right, false, sum);
  }

  static int sumOfLeftLeaves(TreeNode* root) {
    int sum = 0;
    dfs(root, false, sum);  // If tree is 1 node, then it's a left leaf
    return sum;
  }
};