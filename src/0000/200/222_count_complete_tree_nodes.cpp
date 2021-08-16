// 222_count_complete_tree_nodes
// Nevin Zheng
// 8/16/21

#include "Tree.hpp"
#include <fmt/format.h>

using namespace std;

/**
 * Here are some statements that will help us solve this problem
 * In a Perfect Binary tree all levels are filled. The leftmost height
 * and rightmost height are equal.
 * In a perfect binary tree, the number of nodes is 2^h - 1;
 * In a complete binary tree all levels except the last one are completely
 * filled from left to right, there won't be any holes.
 * Thus we have the property that all subtrees of a complete binary tree
 * are complete and may or may not be perfect.
 * We can then use a recursive definition of the number of nodes.
 * If a subtree is prefect we can return 2^h
 * If its not perfect we can return 1 + countNodes(left) + countNodes(right);
 */
class Solution {
 public:
  /**
   * Get the height of the left most node in a tree
   * @param root
   * @return
   */
  static int leftMostHeight(TreeNode* root) {
    if (!root) return 0;
    int h = 1;
    while ((root = root->left)) ++h;
    return h;
  }

  /**
   * Get the height of the right most node in a tree
   * @param root
   * @return
   */
  static int rightMostHeight(TreeNode* root) {
    if (!root) return 0;
    int h = 1;
    while ((root = root->right)) ++h;
    return h;
  }

  int countNodes(TreeNode* root) {
    auto l = leftMostHeight(root);                  // Left Height
    auto r = rightMostHeight(root);                 // Right height
    return (l == r) ? std::pow(2, l) - 1            // Is PBT
                    : 1 + countNodes(root->left) +  // Just complete
                          countNodes(root->right);
  }
};
