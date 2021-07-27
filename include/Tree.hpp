//
// Created by Nevin Zheng on 7/26/21.
//
#pragma once

#include <iosfwd>
#include <string>
#include <utility>

// Definition for a binary tree node.
class TreeNode {
 public:
  int val{0};
  TreeNode* left{nullptr};
  TreeNode* right{nullptr};
  TreeNode() = default;
  explicit TreeNode(int x) : val(x){};
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};
