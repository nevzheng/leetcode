// 1008_construct_binary_search_tree_from_preorder_traversal
// Nevin Zheng
// 7/25/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val{0};
  TreeNode* left{nullptr};
  TreeNode* right{nullptr};
  explicit TreeNode(int x) : val(x) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

TreeNode* bstFromPreorder(const vector<int>& preorder) {
  if (preorder.empty() || preorder.size() == 1) return nullptr;
  auto* root = new TreeNode(preorder.front());
  auto it = find_if(begin(preorder), end(preorder),
                    [&preorder](const auto x) { return x > preorder.front(); });
  vector left(begin(preorder) + 1, it);
  vector right(it, end(preorder));
  root->left = bstFromPreorder(left);
  root->right = bstFromPreorder(right);
  return root;
}

TEST_CASE("1008ex1", "[1008]") {
  const vector<int> preorder = {8, 5, 1, 7, 10, 12};
  const vector<int> expected = {8, 5, 10, 1, 7, -1, 12};
  auto* tree = bstFromPreorder(preorder);
  REQUIRE(tree != nullptr);
}