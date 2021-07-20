// 662_maximum_width_of_binary_tree
// Nevin Zheng
// 7/19/21

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <utils.hpp>

#include <map>

using namespace std;

void findMaxWidth(TreeNode *root, uint64_t x, int depth,
                  map<uint64_t, uint64_t> &levelMap, uint64_t &maxWidth) {
    if (!root) return;
    // First traversal to node stores the level. Traversing left then right, guarantees the left most value is stored first
    if (!levelMap.count(depth)) levelMap.emplace(depth, x);
    // Does this node improve our max width?
    maxWidth = max(maxWidth, x - levelMap.at(depth) + 1);
    // Traverse the left side first, assigning a width of 2*x
    findMaxWidth(root->left, 2 * x, depth + 1, levelMap, maxWidth);
    // Traverse the right side. assigning a width of 2*x+1
    findMaxWidth(root->right, 2 * x + 1, depth + 1, levelMap, maxWidth);
}

// We need to assign a position for each Node
// If we recall from our knowledge of heaps and trees we can uniquely map each
// node of a binary tree into an array.
// For example the root of a subtree is at i, the left node is at 2*i, and the right node
// is at 2*i + 1.
// What we want to know is the difference between the position of the
// right most node and the left most node in the array.
// At Each node we already know the nodes position, but we need to know the
// Left Most Position. In order to have this info, we need to perform
// a preorder traversal. Storing the leftmost node in a hashmap, keyed by level
// When the right node is called, it should not be able to replace the left most value
// This will ensure that the left most value is ready when the right tree is called
using Level = uint64_t;
using LeftMost = uint64_t;
int widthOfBinaryTree(TreeNode *root) {
    uint64_t maxWidth = 0;
    map<Level, LeftMost> levelMap;
    // The Root node is at i=0, in an array
    findMaxWidth(root, 0, 0, levelMap, maxWidth);
    return (int) maxWidth;
}

TEST_CASE("662ex1", "[662]") {
    //    [1,3,2,5,3,null,9]
    auto nine = new TreeNode(9);
    auto three1 = new TreeNode(3);
    auto five = new TreeNode(5);
    auto two = new TreeNode(2, nullptr, nine);
    auto three2 = new TreeNode(3, five, three1);
    auto root = new TreeNode(1, three2, two);
    auto expected = 4;
    REQUIRE(widthOfBinaryTree(root) == expected);
}