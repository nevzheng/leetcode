// 98_validate_binary_search_tree
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

bool validate(TreeNode *root, long min, long max) {
    // Check Range of Current value
    auto rootValid = min < root->val and root->val < max;
    auto leftValid = root->left ? validate(root->left, min, root->val) : true;   // Null is OK
    auto rightValid = root->right ? validate(root->right, root->val, max) : true;// Null is OK
    return rootValid && leftValid && rightValid;
}

bool isValidBST(TreeNode *root) {
    return validate(root, std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
}

//TEST_CASE("98ex1", "[98]") {
//    auto input = {};
//    auto expected = {};
//    REQUIRE(isValidBST(input) == expected);
//}