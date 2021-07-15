//
// Created by Nevin Zheng on 7/14/21.
//
// Definition for a binary tree node.
#include <map>
#include <memory>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool containsOne(TreeNode *root) {
    if (!root) return false;
    auto l = containsOne(root->left);
    auto r = containsOne(root->right);
    if (!l) root->left = nullptr;
    if (!r) root->right = nullptr;
    return root->val == 1 || l || r;
}

TreeNode *pruneTree(TreeNode *root) {
    return containsOne(root) ? root : nullptr;
}