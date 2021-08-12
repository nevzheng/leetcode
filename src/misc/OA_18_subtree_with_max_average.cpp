// OA_18_subtree_with_max_average
// Nevin Zheng
// 8/10/21

// https://algo.monster/problems/subtree_with_maximum_average

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <utility>

using namespace std;

class Node {
 public:
  int val_{};
  vector<Node*> children_;

  Node() = default;
  explicit Node(int val) : val_(val) {}
  Node(int val, vector<Node*> children)
      : val_(val), children_(std::move(children)) {}
};

class Solution {
 public:
  double max_avg_ = INT_MIN;
  Node* best_{};

  struct Subtree {
    int count;
    int sum;
  };

  static bool is_leaf(Node* root) { return root->children_.empty(); }

  Subtree dfs(Node* root) {
    if (!root) return {0, 0};
    if (is_leaf(root)) return {1, root->val_};
    auto count = 1;
    auto sum = root->val_;
    for (const auto& c : root->children_) {
      auto inf = dfs(c);
      count += inf.count;
      sum += inf.sum;
    }

    auto avg = static_cast<double>(sum) / static_cast<double>(count);
    if (avg > max_avg_) {
      max_avg_ = avg;
      best_ = root;
    }
    return {count, sum};
  }

  int maximumAverageSubtree(Node* root) {
    if (!root) return 0;
    dfs(root);
    if (!best_) return 0;
    return best_->val_;
  }
};

TEST_CASE("OA::18::1", "[oa18]") {
  Node* node0 = new Node(20);
  Node* node1 = new Node(12);
  Node* node2 = new Node(18);
  Node* node3 = new Node(11);
  Node* node4 = new Node(2);
  Node* node5 = new Node(3);
  Node* node6 = new Node(15);
  Node* node7 = new Node(8);
  node0->children_ = {node1, node2};
  node1->children_ = {node3, node4, node5};
  node2->children_ = {node6, node7};
  int ans = Solution().maximumAverageSubtree(node0);
  REQUIRE(ans == 18);
}