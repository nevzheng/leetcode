//
// Created by Nevin Zheng on 7/16/21.
//
#include <utils.hpp>
#include <algorithm>
using namespace std;


int diameter(int &maxDiameter, TreeNode *root) {
    if (!root) return 0;
    auto lh = diameter(maxDiameter, root->left);
    auto rh = diameter(maxDiameter, root->right);
    maxDiameter = max(maxDiameter, lh + rh);// Max is either the diameter of a subtree or current global max
    return 1 + max(lh, rh);                 // Extend the longest path
}

int diameterOfBinaryTree(TreeNode *root) {
    auto maxD = -1; // Store our result
    diameter(maxD, root);
    return maxD;
}