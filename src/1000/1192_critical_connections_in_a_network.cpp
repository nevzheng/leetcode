#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using EdgeList = vector<vector<int>>;
using AdjList = vector<vector<int>>;

class TarjanSolver {
 public:
  static constexpr int kUnvisited = -1;
  int n_vertices_;
  AdjList graph_;
  vector<int> ids_;
  vector<int> low_;
  vector<int> parent_;
  int id_ = 0;
  EdgeList bridges_{};

  TarjanSolver(int n_vertices, AdjList graph)
      : n_vertices_(n_vertices),
        graph_(std::move(graph)),
        ids_(vector(n_vertices_, kUnvisited)),
        low_(vector(n_vertices_, kUnvisited)),
        parent_(vector(n_vertices_, kUnvisited)) {}

  void dfs(int u) {
    ids_[u] = low_[u] = id_++;
    for (auto v : graph_[u]) {
      if (ids_[v] == kUnvisited) {
        parent_[v] = u;
        dfs(v);
        low_[u] = min(low_[u], low_[v]);
        if (low_[v] > ids_[u]) bridges_.push_back({u, v});
      } else if (v != parent_[u]) {
        low_[u] = min(low_[u], ids_[v]);
      }
    }
  }

  EdgeList findBridges() {
    for (auto i = 0; i < n_vertices_; i++) {
      if (ids_[i] == kUnvisited) dfs(i);
    }
    return bridges_;
  }
};

AdjList makeAdjList(int n_vertices, const EdgeList& edges) {
  AdjList graph(n_vertices);
  for (auto e : edges) {
    auto [u, v] = tie(e[0], e[1]);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  return graph;
}

EdgeList criticalConnections(int n, const EdgeList& connections) {
  auto graph = makeAdjList(n, connections);
  TarjanSolver tarjan_solver(n, graph);
  return tarjan_solver.findBridges();
}

TEST_CASE("1192ex1", "[1192]") {
  const int n = 4;
  const EdgeList connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
  const EdgeList expected = {{1, 3}};
  auto result = criticalConnections(n, connections);
  REQUIRE(result == expected);
}
