// 987_vertical_order_traversal_of_a_binary_tree
// Nevin Zheng
// 7/18/21

#include "utils.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <map>

using namespace std;

using Val = int;
using Row = int;
using Col = int;
using Map = map<Col, vector<pair<Row, Val>>>;

// Traverse the Tree in O(N) time
// Each Insertion should be lg(N), N = number of nodes.
// Could be improved with a hashmap and some additional sorting
void vertical_traversal(Map &M, TreeNode *root, int row, int col) {
    if (!root) return;
    M[col].emplace_back(row, root->val);
    vertical_traversal(M, root->left, row + 1, col - 1);
    vertical_traversal(M, root->right, row + 1, col + 1);
}

vector<vector<int>> verticalTraversal(TreeNode *root) {
    Map M;
    vertical_traversal(M, root, 0, 0);
    // After Traversal transform the answer
    // Up to N/2 Cols, and a Lg(N) sort per col, so NLGN
    vector<vector<int>> ans;
    for (auto &kv : M) {
        vector<int> v;
        sort(begin(kv.second), end(kv.second), [](const auto &lhs, const auto &rhs) {
            if (lhs.first != rhs.first) return lhs.first < rhs.first;
            return lhs.second < rhs.second;
        });
        transform(begin(kv.second), end(kv.second), back_inserter(v), [](const auto &p) { return p.second; });
        ans.push_back(v);
    }
    return ans;
}

TEST_CASE("987ex1", "[987]") {
    //    vector<string> input = {"3", "9", "20", "null", "null", "15", "7"};
    auto seven = new TreeNode(7);
    auto fifteen = new TreeNode(15);
    auto twenty = new TreeNode(20, fifteen, seven);
    auto nine = new TreeNode(9);
    auto root = new TreeNode(3, nine, twenty);

    vector<vector<int>> expected = {{9}, {3, 15}, {20}, {7}};

    const auto traversal = verticalTraversal(root);
    REQUIRE(traversal == expected);
}

TEST_CASE("987ex2", "[987]") {
    auto four = new TreeNode(4);
    auto five = new TreeNode(5);
    auto six = new TreeNode(6);
    auto seven = new TreeNode(7);

    auto two = new TreeNode(2, four, five);
    auto three = new TreeNode(3, six, seven);

    auto root = new TreeNode(1, two, three);

    vector<vector<int>> expected = {{4}, {2}, {1, 5, 6}, {3}, {7}};

    const auto traversal = verticalTraversal(root);
    REQUIRE(traversal == expected);
}


TEST_CASE("987ex3", "[987]") {
    auto four = new TreeNode(4);
    auto five = new TreeNode(5);
    auto six = new TreeNode(6);
    auto seven = new TreeNode(7);

    auto two = new TreeNode(2, four, six);
    auto three = new TreeNode(3, five, seven);

    auto root = new TreeNode(1, two, three);

    vector<vector<int>> expected = {{4}, {2}, {1, 5, 6}, {3}, {7}};

    const auto traversal = verticalTraversal(root);
    REQUIRE(traversal == expected);
}