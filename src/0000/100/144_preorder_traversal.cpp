// 144_binary_tree_preorder_traversal
// Nevin Zheng
// 8/3/21

#include <bits/stdc++.h>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

// class Solution {
//  public:
//   vector<int> v_;
//
//   void preorder(TreeNode* root) {
//     if (!root) return;
//     v_.push_back(root->val);
//     if (root->left) preorder(root->left);
//     if (root->right) preorder(root->right);
//   }
//
//   vector<int> preorderTraversal(TreeNode* root) {
//     preorder(root);
//     return v_;
//   }
// };

class Solution {
 public:
  vector<int> preorderTraversal(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> stk{{root}};
    vector<int> v;
    while (!stk.empty()) {
      root = stk.top();
      stk.pop();
      v.push_back(root->val);
      if (root->right) stk.push(root->right);
      if (root->left) stk.push(root->left);
    }
    return v;
  }
};
