// 508_most_frequent_subtree_sum
// Nevin Zheng
// 8/2/21

#include <bits/stdc++.h>
#include <fmt/format.h>
#include <Tree.hpp>

using namespace std;

class Solution {
 public:
  map<int, int> sums_;

  int dfs(TreeNode* root) {
    if (!root) return 0;
    auto l = root->left ? dfs(root->left) : 0;
    auto r = root->right ? dfs(root->right) : 0;
    auto sum = root->val + l + r;
    ++sums_[sum];
    return sum;
  }

  vector<int> findFrequentTreeSum(TreeNode* root) {
    dfs(root);
    vector<int> ans;
    auto mx_it = std::max_element(
        sums_.begin(), sums_.end(),
        [](const auto& x, const auto& y) { return x.second < y.second; });
    auto max_freq = mx_it->second;
    for (auto& x : sums_)
      if (x.second == max_freq) ans.push_back(x.first);
    return ans;
  }
};
