// 77_combinations
// Nevin Zheng
// 8/14/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  void combo(vector<int>& v, int x, int n, int k, vector<vector<int>>& ans) {
    if (k == 0) return ans.push_back(v);
    for (auto i = x; i <= n; ++i) {
      v.push_back(i);
      combo(v, i + 1, n, k - 1, ans);
      v.pop_back();
    }
  }

  vector<vector<int>> combine(int n, int k) {
    vector<int> v;
    vector<vector<int>> ans;
    combo(v, 1, n, k, ans);
    return ans;
  }
};

TEST_CASE("77::1", "[77]") {
  const auto n = 4;
  const auto k = 2;
  vector<vector<int>> expected{{2, 4}, {3, 4}, {2, 3}, {1, 2}, {1, 3}, {1, 4}};
  REQUIRE(Solution().combine(n, k) == expected);
}