// 112_path_sum
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

bool dfs(TreeNode *root, int tgt, int sum) {
    if (!root->left and !root->right) return (sum + root->val) == tgt;// isLeaf
    if (root->left and dfs(root->left, tgt, sum + root->val)) return true;
    if (root->right and dfs(root->right, tgt, sum + root->val)) return true;
}

bool hasPathSum(TreeNode *root, int tgt) {
    if (!root) return false;
    return dfs(root, tgt, 0);
}


//TEST_CASE("112ex1", "[112]") {
//    auto input = {};
//    auto expected = {};
//    REQUIRE(hasPathSum(input) == expected);
//}