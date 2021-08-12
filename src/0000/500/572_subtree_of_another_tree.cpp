// 572_subtree_of_another_tree
// Nevin Zheng
// 8/11/21

#include "Tree.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  /**
   * Determine if root and subroot are the same tree
   * @param root
   * @param subroot
   * @return
   */
  bool equals(TreeNode* root, TreeNode* subRoot) {
    if (!root && !subRoot) return true;
    if (!root || !subRoot || root->val != subRoot->val) return false;
    return equals(root->left, subRoot->left) &&
           equals(root->right, subRoot->right);
  }

  bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;
    // Check Current Root, then recursively match subtrees
    return equals(root, subRoot) || isSubtree(root->left, subRoot) ||
           isSubtree(root->right, subRoot);
  }
};