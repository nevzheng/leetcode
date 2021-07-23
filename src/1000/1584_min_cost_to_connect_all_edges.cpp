// 1584_min_cost_to_connect_all_edges
// Nevin Zheng
// 7/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// public:
//  using Cost = int;
//  using V = int;
//  using Edge = pair<Cost, V>;
//  using MinHeap = priority_queue<Edge, vector<Edge>, std::greater<>>;
//  using AdjList = vector<vector<Edge>>;
//  int minCostConnectPoints(const vector<vector<int>>& points) {
//    auto n_vertices = static_cast<int>(points.size());
//    auto mst_cost = 0;
//    AdjList graph(n_vertices);
//    vector dist(n_vertices, INT_MIN);
//    vector vis(n_vertices, false);
//    vector pred(n_vertices, -1);
//    // Build Our Adjacency List
//    for (auto u = 0; u < n_vertices - 1; u++) {
//      for (auto v = 1; v < n_vertices; v++) {
//        auto [a, b] = tie(points[u], points[v]);
//        auto cost = abs(a[0] - b[0]) + abs(a[1] - b[1]);
//        graph[u].push_back({cost, v});
//        graph[v].push_back({cost, u});
//      }
//    }
//    // Do Prims Algorithm
//    MinHeap pq;
//    auto edge_count = 0;
//    auto src = 0;  // Pick zero index to be source
//    dist[src] = 0;
//    vis[src] = true;
//    for (auto wv : graph[src]) pq.push(wv);  // Push neighbors of src
//    while (!pq.empty()) {
//      auto [cost, u] = pq.top();
//      pq.pop();
//      if (vis[u]) continue;  // Skip edge which are already included
//      // Include vertex and add cost to truee
//      vis[u] = true;
//      dist[u] = cost;
//      mst_cost += cost;
//      edge_count++;
//      for (auto wv : graph[u]) {
//        auto [w, v] = wv;
//        if (!vis[v]) pq.push(wv);
//      }
//    }
//    if (edge_count != n_vertices - 1) return -1;  // Spanning Tree Not Found
//    return mst_cost;
//  }

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