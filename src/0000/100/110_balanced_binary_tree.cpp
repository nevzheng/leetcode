// 110_balanced_binary_tree
// Nevin Zheng
// 8/4/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

// class Solution {
//  public:
//   map<TreeNode*, int> h_map;
//   int height(TreeNode* root) {
//     if (!root) return 0;
//     if (auto it = h_map.find(root); it != h_map.end()) return it->second;
//     auto l = root->left ? height(root->left) : 0;
//     auto r = root->right ? height(root->right) : 0;
//     return h_map[root] = 1 + max(l, r);
//   }
//
//   bool isBalanced(TreeNode* root) {
//     if (!root) return true;
//     auto l_balance = isBalanced(root->left);
//     auto r_balance = isBalanced(root->right);
//     auto l = height(root->left);
//     auto r = height(root->right);
//     return (abs(l - r) <= 1) and l_balance and r_balance;
//   }
// };

class Solution {
 public:
  struct Info {
    bool balanced;
    int height;
  };

  Info check_balance(TreeNode* root) {
    if (!root) return {true, 0};
    auto [lb, lh] = check_balance(root->left);
    auto [rb, rh] = check_balance(root->right);
    return {abs(lh - rh) <= 1 && lb && rb, 1 + max(lh, rh)};
  }

  bool isBalanced(TreeNode* root) { return check_balance(root).balanced; }
};
