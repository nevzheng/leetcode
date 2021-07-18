// 513_find_bottom_left_tree_value
// Nevin Zheng
// 7/18/21

#include <utility>

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <utils.hpp>

using namespace std;

bool isLeaf(TreeNode *root) {
    return root && !root->right && !root->left;
}

// Tuples are lexographically compared left to right
// Thus we just need to make height and leftness  positive integers, bigger is better.
// That way we don't have to use custom comparison
// O(N) time and memory
using Height = int;
using Leftness = int;
using Value = int;
// Return a Tuple representing the height, leftness, and value bottom left node the the tree
tuple<Height, Leftness, Value> dfs(TreeNode *root, int height, int left) {
    if (isLeaf(root)) return make_tuple(height, left, root->val);
    auto l = root->left ? dfs(root->left, height + 1, left + 1) : make_tuple(-1, -1, -1);
    auto r = root->right ? dfs(root->right, height + 1, left - 1) : make_tuple(-1, -1, -1);
    return max(l, r);
}

int findBottomLeftValue(TreeNode *root) {
    return std::get<2>(dfs(root, 0, 0));
}

//TEST_CASE("513ex1", "[513]") {
//    auto input = {};
//    auto expected = {};
//    REQUIRE(find_bottom_left_tree_value(input) == expected);
//}