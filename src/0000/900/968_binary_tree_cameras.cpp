// 968_binary_tree_cameras
// Nevin Zheng
// 7/26/21

#include "Tree.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// This Formulation is correct and show good thinking, but it performs poorly
//
// using PlaceCamera = bool;
// using ParentCovered = bool;
// using State = tuple<TreeNode*, PlaceCamera, ParentCovered>;
// using Cache = map<State, int>;
//
// int solve(Cache& dp, TreeNode* root, bool place_camera, bool parent_covered)
// {
//   // Can't Place camera at null / Base Case
//   if (!root) return place_camera ? INT16_MAX : 0;
//   if (!root->left and !root->right) {       // We're at a leaf node
//     if (place_camera) return 1;             // Placed Camera at leaf
//     return parent_covered ? 0 : INT16_MAX;  // Only valid if parent covered
//   }
//   if (auto kv = dp.find({root, place_camera, parent_covered}); kv != end(dp))
//   {
//     return kv->second;  // Cache Hit
//   }
//   if (place_camera) {
//     // Add 1 since we're placing a camera here
//     // Then make a call informing children that we placed a camera
//     // taking the min
//     return dp[{root, place_camera, parent_covered}] =
//                1 +
//                min(solve(dp, root->left, false, true),
//                    solve(dp, root->left, true, true)) +
//                min(solve(dp, root->right, false, true),
//                    solve(dp, root->right, true, true));
//   }
//   if (parent_covered) {
//     // Parent is covered, so we don't have to place a camera
//     // Make calls informing children as such
//     // taking the min
//     return dp[{root, place_camera, parent_covered}] =
//                min(solve(dp, root->left, true, false),
//                    solve(dp, root->left, false, false)) +
//                min(solve(dp, root->right, true, false),
//                    solve(dp, root->right, false, false));
//   }
//   // Parent isn't covered. We have to tell children they need to place
//   // We can either have 1 camera in the left tree or the right three
//   // we'll take the min of the two options
//
//   // Force Left to place, taking the min of right
//   auto place_left = solve(dp, root->left, true, false) +
//                     min(solve(dp, root->right, true, false),
//                         solve(dp, root->right, false, false));
//   // Force right to place, taking the min of left
//   auto place_right = solve(dp, root->right, true, false) +
//                      min(solve(dp, root->left, true, false),
//                          solve(dp, root->left, false, false));
//   return dp[{root, place_camera, parent_covered}] =
//              min(place_left, place_right);
// }
//
// int minCameraCover(TreeNode* root) {
//   Cache dp;
//   return min(solve(dp, root, false, false), solve(dp, root, true, false));
// }

enum class NodeStatus { kHasCamera, kHasCover, kNeedCover };

NodeStatus dfs(TreeNode* root, int& cameras) {
  if (!root) return NodeStatus::kHasCover;        // Null Nodes are Covered
  auto left_status = dfs(root->left, cameras);    // Try to cover the left
  auto right_status = dfs(root->right, cameras);  // Try to cover right
  if (left_status == NodeStatus::kNeedCover ||
      right_status == NodeStatus::kNeedCover) {
    cameras++;
    return NodeStatus::kHasCamera;
  }
  if (left_status == NodeStatus::kHasCamera ||
      right_status == NodeStatus::kHasCamera) {
    return NodeStatus::kHasCover;
  }
  return NodeStatus::kNeedCover;
}

int minCameraCover(TreeNode* root) {
  int cameras = 0;
  return dfs(root, cameras) == NodeStatus::kNeedCover ? ++cameras : cameras;
}

TEST_CASE("968ex1", "[968]") {
  auto* one = new TreeNode(0);
  auto* two = new TreeNode(0);
  auto* three = new TreeNode(0, one, two);
  auto* root = new TreeNode(0, three, nullptr);
  auto expected = 1;
  REQUIRE(minCameraCover(root) == expected);
}

TEST_CASE("968ex2", "[968]") {
  auto* one = new TreeNode(0);
  auto* two = new TreeNode(0, nullptr, one);
  auto* three = new TreeNode(0, two, nullptr);
  auto* four = new TreeNode(0, three, nullptr);
  auto* root = new TreeNode(0, four, nullptr);
  auto expected = 2;
  REQUIRE(minCameraCover(root) == expected);
}