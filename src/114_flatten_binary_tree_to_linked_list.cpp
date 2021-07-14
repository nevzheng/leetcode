// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
// Created by Nevin Zheng on 7/13/21.
//

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode *getRightMost(TreeNode *root) {
        while (root->right) root = root->right;
        return root;
    }

    // This is best visualized via diagram
    // We can transform the tree by pointing the right most element of left subtree of a node to the right subtree
    // so we need a function to get the right most element
    // a way to access the left element
    // then we can rearrange the ptrs
    void flatten(TreeNode *root) {
        auto curr = root;
        while (curr) {
            auto left = curr->left;
            if (left) {
                auto right_most = getRightMost(left);
                right_most->right=curr->right;
                curr->right=curr->left;
                curr->left = nullptr;
            }
            curr = curr ->right;
        }
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
//class Solution {
//public:
//    // Approach 1, Perform a Preorder traversal
//    // and store the result in a vector
//    // We can then perform a transformation on the vector to proudce
//    // the linked list
//    // O(N) time and space
//    void flatten(TreeNode* root) {
//        if(!root) return;
//        vector<TreeNode*> v;
//        preorder(v, root); // Get the preorder traversal
//        auto n = v.size();
//        for(auto i=0; i< n-1; i++){
//            // It's a singly linked list. can do double, but ignore
//            v[i]->left  = nullptr;
//            v[i]->right = v[i+1]; // point to the next element
//        }
//        // Fix up the last element
//        v[n-1]->right = nullptr;
//        v[n-1]->left = nullptr;
//
//    }
//
//    void preorder(vector<TreeNode*>& v, TreeNode* root){
//        if(!root) return;
//        v.push_back(root); // Push the pointer onto the vec
//        preorder(v, root->left); // Go Left
//        preorder(v, root->right); // Go Right
//    }
//};
