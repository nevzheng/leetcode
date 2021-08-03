// 145_binary_tree_postorder_traversal
// Nevin Zheng
// 8/3/21

#include <bits/stdc++.h>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

// class Solution {
//  public:
//   vector<int> v_;
//   void postorder(TreeNode* root) {
//     if (!root) return;
//     postorder(root->left);
//     postorder(root->right);
//     v_.push_back(root->val);
//   }
//   vector<int> postorderTraversal(TreeNode* root) {
//     postorder(root);
//     return v_;
//   }
// };

class Solution {
 public:
  vector<int> postorderTraversal(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> path;
    stack<TreeNode*> children{{root}};
    vector<int> v;
    while (!children.empty()) {
      root = children.top();
      if (!path.empty() and path.top() == root) {
        v.push_back(root->val);
        path.pop();
        children.pop();
      } else {
        path.push(root);
        if (root->right) children.push(root->right);
        if (root->left) children.push(root->left);
      }
    }
    return v;
  }
};