// 988_smallest_string_starting_from_leaf
// Nevin Zheng
// 8/1/21

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

class Solution {
 public:
  string min_;
  string prefix_;
  void dfs(TreeNode* root) {
    if (!root) return;
    prefix_ += static_cast<char>(root->val) + 'a';
    if (!root->left and !root->right) {  // At Leaf Node, check
      auto cpy = prefix_;
      reverse(begin(cpy), end(cpy));
      min_ = min_.empty() ? cpy : min(min_, cpy);
    }
    if (root->left) dfs(root->left);
    if (root->right) dfs(root->right);
    // Pop Back Root's char
    prefix_.pop_back();
  }

  string smallestFromLeaf(TreeNode* root) {
    dfs(root);
    return min_;
  }
};

TEST_CASE("988ext", "[988]") {}