// 94_binary_tree_inorder_traversal
// Nevin Zheng
// 8/3/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

class Solution {
 public:
  vector<int> v_;

  void inorder(TreeNode* root) {
    if (!root) return;
    v_.push_back(root->val);
    if (root->left) inorder(root->left);
    if (root->right) inorder(root->right);
  }

  vector<int> inorderTraversal(TreeNode* root) {
    inorder(root);
    return v_;
  }
};

/**
 * Iterative Inorder Traversal
 */
// class Solution {
//  public:
//   vector<int> inorderTraversal(TreeNode* root) {
//     vector<int> v;
//     stack<TreeNode*> stk;
//
//     while(root or !stk.empty()){
//       while(root){
//         stk.push(root);
//         root=root->left;
//       }
//       root=stk.top();
//       stk.pop();
//       v.push_back(root->val);
//       root=root->right;
//     }
//     return v;
//   }
// };

TEST_CASE("94ex1", "[94]") {
  auto input = {};
  auto expected = {};
  REQUIRE((input) == expected);
}