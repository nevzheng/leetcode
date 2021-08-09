// 429_nary_tree_level_order_traversal
// Nevin Zheng
// 8/6/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// Definition for a Node.
class Node {
 public:
  int val{0};
  vector<Node*> children;
  Node() = default;
  explicit Node(int _val) : val(_val) {}
  explicit Node(int _val, vector<Node*> _children)
      : val(_val), children(std::move(_children)) {}
};

class Solution {
 public:
  vector<vector<int>> levels_;
  void dfs(Node* root, size_t level) {
    if (!root) return;
    if (level >= levels_.size()) levels_.emplace_back();
    levels_.at(level).push_back(root->val);
    for (auto* child : root->children) dfs(child, level + 1);
  }
  vector<vector<int>> levelOrder(Node* root) {
    dfs(root, 0);
    return levels_;
  }
};