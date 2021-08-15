// 257_binary_tree_paths
// Nevin Zheng
// 8/14/21

#inlcude "Tree.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static void dfs(TreeNode* root, vector<int>& path, vector<vector<int>>& ans) {
    if (!root) return;
    path.push_back(root->val);
    if (!root->left and !root->right) ans.push_back(path);
    if (root->left) dfs(root->left, path, ans);    // Explore Left
    if (root->right) dfs(root->right, path, ans);  // Explore Right
    path.pop_back();
  }
  static string stringify(vector<int>& path) {
    const string sep = "->";
    string ans;
    auto last = path.back();
    path.pop_back();
    for (auto i : path) ans += to_string(i) + sep;
    ans += to_string(last);
    return ans;
  }

  static vector<string> binaryTreePaths(TreeNode* root) {
    vector<vector<int>> ans;
    vector<int> path;
    dfs(root, path, ans);
    vector<string> anss;
    for (auto& v : ans) anss.push_back(stringify(v));
    return anss;
  }
};