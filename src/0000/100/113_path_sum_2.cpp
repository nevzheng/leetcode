// 113_path_sum_2
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

//
//bool isLeaf(TreeNode* node){
//    return !node->left and !node->right;
//}
//
//// This Solution is clean, but it uses a lot of memory as path needs to be copied at each branch
//// an iterative solution with a stack would be more efficent.
//using PathVec = vector<vector<int>>;
//void dfs(PathVec& paths, const int& tgt, TreeNode*root, vector<int> path, int sum){
//    sum += root->val; // update sum of path
//    path.push_back(root->val); // update path
//
//    if(isLeaf(root) and sum==tgt) paths.push_back(path);
//
//    if(root->left) dfs(paths, tgt, root->left, path, sum);
//    if(root->right) dfs(paths, tgt, root->right, path, sum);
//}
//
//vector<vector<int>> pathSum(TreeNode* root, int tgt) {
//    if(!root) return {};
//
//    vector<vector<int>> ans;
//    vector<int> path;
//    dfs(ans, tgt, root, path, 0);
//    return ans;
//}


TEST_CASE("113ex1", "[113]") {
    auto input = {};
    auto expected = {};
    REQUIRE(pathSum3(input) == expected);
}