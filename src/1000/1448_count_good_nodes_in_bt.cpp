// 1448_count_good_nodes_in_bt
// Nevin Zheng
// 8/17/21

#include "Tree.hpp"

using namespace std;

class Solution {
 public:
  /**
   * Count the number of good nodes in a tree rooted at root
   * @param root Root of a binary tree
   * @param p_max Maximum value on path to root
   * @param count Number of good nodes
   */
  void dfs(TreeNode* root, int p_max, int& count) {
    if (!root) return;
    if (root->val >= p_max) ++count;
    if (root->left) dfs(root->left, max(p_max, root->val), count);
    if (root->right) dfs(root->right, max(p_max, root->val), count);
  }

  int goodNodes(TreeNode* root) {
    int count = 0;
    dfs(root, INT_MIN, count);
    return count;
  }
};