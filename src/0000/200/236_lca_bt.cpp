// 236_lca_bt
// Nevin Zheng
// 8/15/21

#include <Tree.hpp>

using namespace std;

/**
 * We will perform a post order traversal where we process the tree from the
 * bottom up. If we find the target node, we'll return the root
 * O(N) time and space
 */
class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    if (root == p || root == q) return root;  // We found p or q
    // Search for p and q in l and r subtrees
    auto* l = root->left ? lowestCommonAncestor(root->left, p, q) : nullptr;
    auto* r = root->right ? lowestCommonAncestor(root->right, p, q) : nullptr;
    if (!l) return r;
    if (!r) return l;
    return root;  // l && r => root is lca
  }
};
