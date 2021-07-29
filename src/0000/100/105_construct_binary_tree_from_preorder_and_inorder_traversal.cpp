// 105_construct_binary_tree_from_preorder_and_inorder_traversal
// Nevin Zheng
// 7/27/21

#include "Tree.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

vector<int> sliceVector(const vector<int>& v, size_t left, size_t right) {
  return vector(begin(v) + left, begin(v) + right);
}

TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
  auto len = preorder.size();
  if (preorder.empty() or inorder.empty()) return nullptr;
  auto* root = new TreeNode(preorder.front());
  auto mid =
      find(begin(inorder), end(inorder), preorder.front()) - begin(inorder);
  root->left = buildTree(sliceVector(preorder, 1, mid + 1),
                         sliceVector(inorder, 0, mid));
  root->right = buildTree(sliceVector(preorder, mid + 1, len),
                          sliceVector(inorder, mid + 1, len));
  return root;
}

TEST_CASE("105ex1", "[105]") {
  const vector<int> preorder = {3, 9, 20, 15, 7};
  const vector<int> inorder = {9, 3, 15, 20, 7};
  auto* result = buildTree(preorder, inorder);
  REQUIRE(result != nullptr);
}