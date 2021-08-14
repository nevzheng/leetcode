//
// Created by Nevin Zheng on 7/25/21.
//
#pragma once

#include <stack>
#include <vector>

using namespace std;

using EdgeList = vector<vector<int>>;
using AdjList = vector<vector<int>>;

class TarjanSolver {
 private:
  constexpr static int kUnvisited = -1;
  bool solved_ = false;
  int n_vertices_, id_ = 0, scc_count_ = 0;
  AdjList graph_;
  vector<int> ids_, low_, scc_;
  vector<bool> on_stk_;
  stack<int> stk_;

 public:
  TarjanSolver(int nVertices, AdjList graph);

  void dfs(int u);

  void solve();
};
