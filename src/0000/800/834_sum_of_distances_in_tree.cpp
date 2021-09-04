// 834_sum_of_distances_in_tree
// Nevin Zheng
// 9/4/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  vector<vector<int>> v;
  vector<int> counter;  // Number of nodes in subtrees rooted at n
  vector<int> res;      // Total Distance to other nodes

  void dfs(int i, int p) {
    for (auto u : v[i]) {
      if (u == p) continue;
      dfs(u, i);
      counter[i] += counter[u];       // Count number of nodes in subtree
      res[i] += res[u] + counter[u];  // add child result and count of subtree
    }
  }

  void dfs2(int i, int n, int p) {
    for (auto u : v[i]) {
      if (u == p) continue;
      res[u] = res[i] - counter[u] + n - counter[u];
      dfs2(u, n, i);
    }
  }

  vector<int> sumOfDistancesInTree(int n, const vector<vector<int>>& edges) {
    v.resize(n);
    for (int i = 0; i < n - 1; i++) {
      int a = edges[i][0];
      int b = edges[i][1];
      v[a].push_back(b);
      v[b].push_back(a);
    }
    res.resize(n);
    counter = vector(n, 1);  // Each subtree starts w/ 1 node
    dfs(0, -1);
    dfs2(0, n, -1);
    return res;
  }
};

TEST_CASE("834::1", "{834}") {
  const int n = 6;
  const vector<vector<int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}};
  const vector<int> expected{8, 12, 6, 10, 10, 10};
  REQUIRE(Solution().sumOfDistancesInTree(n, edges) == expected);
}