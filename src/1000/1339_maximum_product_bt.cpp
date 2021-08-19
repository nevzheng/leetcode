// 1339_maximum_product_bt
// Nevin Zheng
// 8/19/21

#include "Tree.hpp"
#include <catch2/catch.hpp>

using namespace std;

/**
 * We will first find the sum of the whole tree and store it in an int64
 * We'll do a post order traversal taking the max of
 * (total - l)*l, (total-r)*r, gMax
 * we then return gMax % kMod=1e9+7
 */
class Solution {
 public:
  constexpr static int kMod = 1e9 + 7;

  static int64_t treeSum(TreeNode* root) {
    if (!root) return 0;
    return root->val + treeSum(root->left) + treeSum(root->right);
  }

  static int64_t dfs(TreeNode* root, int64_t total, int64_t& mx) {
    if (!root) return 0;
    auto l_sum = dfs(root->left, total, mx);
    auto r_sum = dfs(root->right, total, mx);
    // Take the best option
    mx = max({mx,                           // i. Current Best
              (total - l_sum) * (l_sum),    // ii. Cut Left Subtree
              (total - r_sum) * (r_sum)});  // iii. Cut Right Subtree
    return root->val + l_sum + r_sum;       // Return subtree sum
  }

  static int maxProduct(TreeNode* root) {
    int64_t mx = INT_MIN;
    // Compute sum of the whole tree
    auto total = treeSum(root);
    dfs(root, total, mx);
    return static_cast<int>(mx % kMod);
  }
};

TEST_CASE("1339::1", "[1339]") {
  auto four = make_unique<TreeNode>(4);
  auto five = make_unique<TreeNode>(5);
  auto six = make_unique<TreeNode>(6);
  auto two = make_unique<TreeNode>(2, four.get(), five.get());
  auto three = make_unique<TreeNode>(3, six.get(), nullptr);
  auto one = make_unique<TreeNode>(1, two.get(), three.get());
  const auto expected = 110;
  REQUIRE(Solution().maxProduct(one.get()) == expected);  // Use Leetcode
}

TEST_CASE("1339::2", "[1339]") {
  auto five = make_unique<TreeNode>(5);
  auto six = make_unique<TreeNode>(6);

  auto three = make_unique<TreeNode>(3);
  auto four = make_unique<TreeNode>(4, five.get(), six.get());

  auto two = make_unique<TreeNode>(2, three.get(), four.get());
  auto one = make_unique<TreeNode>(1, nullptr, two.get());
  const auto expected = 90;
  REQUIRE(Solution().maxProduct(one.get()) == expected);  // Use Leetcode
}

TEST_CASE("1339::3", "[1339]") {
  auto one = make_unique<TreeNode>(1);
  auto root = make_unique<TreeNode>(1, one.get(), nullptr);
  const auto expected = 1;
  REQUIRE(Solution().maxProduct(root.get()) == expected);  // Use Leetcode
}

TEST_CASE("1339::4", "[1339]") {
  auto one = make_unique<TreeNode>(1);
  auto eleven = make_unique<TreeNode>(11);
  auto four = make_unique<TreeNode>(4);
  auto five = make_unique<TreeNode>(5);

  auto ten = make_unique<TreeNode>(10, five.get(), four.get());
  auto seven = make_unique<TreeNode>(7, eleven.get(), one.get());
  auto eight = make_unique<TreeNode>(8);
  auto six = make_unique<TreeNode>(6);

  auto three = make_unique<TreeNode>(3, ten.get(), seven.get());
  auto nine = make_unique<TreeNode>(9, eight.get(), six.get());

  auto root = make_unique<TreeNode>(2, three.get(), nine.get());

  const auto expected = 1025;
  REQUIRE(Solution().maxProduct(root.get()) == expected);  // Use Leetcode
}