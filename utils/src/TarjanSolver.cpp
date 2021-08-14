// TarjanSolver.cpp
// Created by Nevin Zheng on 7/25/21.
//

//
// Created by Nevin Zheng on 7/25/21.
//

#include "TarjanSolver.hpp"

TarjanSolver::TarjanSolver(int nVertices, AdjList graph)
    : n_vertices_(nVertices),
      graph_(move(graph)),
      ids_(vector(nVertices, kUnvisited)),
      low_(vector(nVertices, kUnvisited)),
      scc_(vector(nVertices, kUnvisited)),
      on_stk_(vector(nVertices, false)) {}

void TarjanSolver::dfs(int u) {
  ids_[u] = low_[u] = id_++;
  stk_.push(u);
  on_stk_[u] = true;
  for (auto v : graph_[u]) {
    if (ids_[v] == kUnvisited) {
      dfs(v);
      low_[u] = min(low_[u], low_[v]);
    } else if (on_stk_[v]) {  // BackEdge Detected. Might need to pull v's id
      low_[u] = min(low_[u], ids_[v]);
    }
  }
  // U is Root of an SCC. Pop nodes and assign scc id
  if (low_[u] == ids_[u]) {
    while (true) {
      auto node = stk_.top();
      stk_.pop();
      scc_[node] = scc_count_;
      on_stk_[node] = false;
      if (node == u) break;
    }
    scc_count_++;
  }
}

void TarjanSolver::solve() {
  if (solved_) return;
  for (auto u = 0; u < n_vertices_; u++) {
    if (ids_[u] == kUnvisited) dfs(u);
  }
  solved_ = true;
}

//#include <catch2/catch.hpp>
// TEST_CASE("tarjan1") {
//  const auto n_vertices = 5;
//  const auto n_edges = 6;
//  const EdgeList = {{1, 4}, {1, 3}, {2, 4}, {3, 4}, {4, 5}, {5, 1}};
//  TarjanSolver ts(5, graph);
//  ts.solve();
//  auto scc_id = ts.getComponents();
//  auto n_components = ts.getComponentCount();
//  auto even{0}, odd{0};
//  for (auto n = 0; n < n_components; n++) {
//    auto x = count(begin(scc_id), end(scc_id), n);
//    x % 2 ? odd += x : even += x;
//  }
//  auto result = (odd - even);
//  const auto expected = -3;
//  require(result == expected);
//}
