// 199_binary_tree_right_side_view
// Nevin Zheng
// 8/1/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <Tree.hpp>
using namespace std;

class Solution {
 public:
  //  map<int, int> s_right_;
  set<int> seen_;
  vector<int> s_right_;

  void dfs(TreeNode* root, int level) {
    if (!root) return;
    if (!seen_.count(level)) {
      seen_.insert(level);
      s_right_.push_back(root->val);
    }
    if (root->right) dfs(root->right, level + 1);
    if (root->left) dfs(root->left, level + 1);
  }

  vector<int> rightSideView(TreeNode* root) {
    dfs(root, 0);
    return s_right_;
  }
};

TEST_CASE("199ex1", "[199]") {}