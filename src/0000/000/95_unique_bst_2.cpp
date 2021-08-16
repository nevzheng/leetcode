// 95_unique_bst_2
// Nevin Zheng
// 8/16/21

#include "Tree.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  vector<TreeNode*> generate(int l, int r) {
    if (l > r) return {nullptr};  // Base Case
    vector<TreeNode*> trees;
    for (auto i = l; i <= r; ++i) {
      auto lefts = generate(l, i - 1);
      auto rights = generate(i + 1, r);
      for (auto* lft : lefts) {
        for (auto* rgt : rights) {
          trees.push_back(new TreeNode(i, lft, rgt));
        }
      }
    }
    return trees;
  }

  vector<TreeNode*> generateTrees(int n) {
    return n ? generate(1, n) : vector<TreeNode*>();
  }
};
