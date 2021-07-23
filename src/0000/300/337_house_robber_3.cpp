// 337_house_robber_3
// Nevin Zheng
// 7/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val{0};
  TreeNode* left{nullptr};
  TreeNode* right{nullptr};
  TreeNode() = default;
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

// using Cache = map<pair<TreeNode*, bool>, int>;
//
// template <typename T1, typename T2, typename... Tail>
// constexpr auto max(T1&& t1, T2&& t2, Tail&&... tail) {
//   if constexpr (sizeof...(tail) == 0) {
//     return t1 > t2 ? t1 : t2;
//   } else {
//     return max(max(t1, t2), tail...);
//   }
// }
//
// int dfs(Cache& cache, TreeNode* root, bool take) {
//   if (!root) return 0;
//   if (cache.count({root, take})) return cache[{root, take}];
//   auto skip_left = root->left ? dfs(cache, root->left, false) : 0;
//   auto skip_right = root->right ? dfs(cache, root->right, false) : 0;
//   if (take) {
//     // Take this value and then have to skip the next layer
//     auto result = root->val + skip_left + skip_right;
//     return cache[{root, take}] = result;
//   }
//   auto take_left = root->left ? dfs(cache, root->left, true) : 0;
//   auto take_right = root->right ? dfs(cache, root->right, true) : 0;
//   auto result = max(skip_left + take_right, take_left + skip_right,
//                     skip_left + skip_right, take_right + take_left);
//   return cache[{root, take}] = result;
// }
//
///**
// * At each node we can make a decision to take or not take a node
// * @param root
// * @return
// */
// int rob(TreeNode* root) {
//  Cache cache;
//  return max(dfs(cache, root, true), dfs(cache, root, false));
//}

int dfs(TreeNode* root, map<TreeNode*, int>& cache) {
  if (!root) return 0;
  if (cache.count(root)) return cache[root];
  auto rob_next_left =
      root->left ? dfs(root->left->left, cache) + dfs(root->left->right, cache)
                 : 0;
  auto rob_next_right = root->right ? dfs(root->right->left, cache) +
                                          dfs(root->right->right, cache)
                                    : 0;
  return cache[root] = max(root->val + rob_next_right + rob_next_left,
                           dfs(root->right, cache) + dfs(root->left, cache));
}

int rob(TreeNode* root) {
  map<TreeNode*, int> cache;
  return dfs(root, cache);
}

TEST_CASE("337ex1", "[337]") {
  auto* one = new TreeNode(1);
  auto* three_right = new TreeNode(3, nullptr, one);
  auto* three_left = new TreeNode(3);
  auto* two = new TreeNode(2, nullptr, three_left);
  auto* root = new TreeNode(3, two, three_right);
  auto expected = 7;
  REQUIRE(rob(root) == expected);
}

TEST_CASE("337ex2", "[337]") {
  auto* one_left = new TreeNode(1);
  auto* three = new TreeNode(3);
  auto* one_right = new TreeNode(1);
  auto* five = new TreeNode(5, nullptr, one_right);
  auto* four = new TreeNode(4, one_left, three);
  auto* root = new TreeNode(3, four, five);
  auto expected = 9;
  REQUIRE(rob(root) == expected);
}

TEST_CASE("337ex3", "[337]") {
  auto* four = new TreeNode(4);
  auto* one = new TreeNode(1, nullptr, four);
  auto* three = new TreeNode(3);
  auto* root = new TreeNode(2, one, three);
  auto expected = 7;
  REQUIRE(rob(root) == expected);
}