// 1584_min_cost_to_connect_all_edges
// Nevin Zheng
// 7/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using AdjMatrix = vector<vector<int>>;

int findMinIndex(const int n_vertices, const vector<int>& distance,
                 const vector<bool>& visited) {
  auto min_index = -1;
  auto min_val = INT_MAX;
  for (auto i = 0; i < n_vertices; i++) {
    if (!visited[i] and distance[i] < min_val) {
      min_val = distance[i];
      min_index = i;
    }
  }
  return min_index;
}
int minCostConnectPoints(const vector<vector<int>>& points) {
  auto n_vertices = static_cast<int>(points.size());
  vector dist(n_vertices, INT_MAX);  // Cost of Including an node in graph
  dist[0] = 0;                       // Init a vertex in mst to dist 0
  vector vis(n_vertices, false);     // Has a Node been Included yet
  for (auto i = 0; i < n_vertices; i++) {
    auto u = findMinIndex(n_vertices, dist, vis);
    vis[u] = true;
    for (auto v = 0; v < n_vertices; v++) {
      auto [p1, p2] = tie(points[u], points[v]);
      auto cost = abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
      if (!vis[v] and dist[v] > cost) dist[v] = cost;
    }
  }
  return std::accumulate(begin(dist), end(dist), 0);
}

TEST_CASE("1584ex1", "[1584]") {
  const vector<vector<int>> input = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
  const auto expected = 20;
  REQUIRE(minCostConnectPoints(input) == expected);
}

TEST_CASE("1584ex2", "[1584]") {
  const vector<vector<int>> input = {{3, 12}, {-2, 5}, {-4, 1}};
  const auto expected = 18;
  REQUIRE(minCostConnectPoints(input) == expected);
}

TEST_CASE("1584ex3", "[1584]") {
  const vector<vector<int>> input = {{0, 0}, {1, 1}, {1, 0}, {-1, 1}};
  const auto expected = 4;
  REQUIRE(minCostConnectPoints(input) == expected);
}

TEST_CASE("1584ex4", "[1584]") {
  const vector<vector<int>> input = {{-1000000, -1000000}, {1000000, 1000000}};
  const auto expected = 4000000;
  REQUIRE(minCostConnectPoints(input) == expected);
}

TEST_CASE("1584ex5", "[1584]") {
  const vector<vector<int>> input = {{0, 0}};
  const auto expected = 0;
  REQUIRE(minCostConnectPoints(input) == expected);
}