// 1584_min_cost_to_connect_all_edges
// Nevin Zheng
// 7/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using Cost = int;
using V = int;
using Edge = pair<Cost, V>;
using AdjList = vector<vector<Edge>>;
using CostMap = map<pair<int, int>, int>;

int minCostConnectPoints(const vector<vector<int>>& points) {
  auto n_vertices = static_cast<int>(points.size());
  CostMap cost_map;
  AdjList graph(n_vertices);
  for (auto i = 0; i < n_vertices - 1; i++) {
    for (auto j = i + 1; j < n_vertices; j++) {
      auto [p1, p2] = tie(points[i], points[j]);
      auto cost = abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
      graph[i].push_back({cost, j});
      graph[j].push_back({cost, i});
      cost_map[{i, j}] = cost;
      cost_map[{j, i}] = cost;
    }
  }
  vector<int> costs(n_vertices, INT_MAX);  // Costs
  vector<int> pred(n_vertices, -1);        // predecessors in the MST
  vector<bool> included(n_vertices, false);
  priority_queue<Edge, vector<Edge>, greater<>> pq;
  pq.push({0, 0});  // Push (cost=0, src=0) onto queue
  while (!pq.empty()) {
    auto [_, u] = pq.top();
    pq.pop();
    if (included[u]) continue;
    included[u] = true;
    for (auto x : graph[u]) {
      auto [cost, v] = x;
      if (!included[v] and costs[v] > cost) {
        costs[v] = cost;
        pred[v] = u;
        pq.push({costs[v], v});
      }
    }
  }
  auto cost = 0;
  for (auto i = 1; i < n_vertices; i++) {
    auto [u, v] = tie(i, pred[i]);
    cost += cost_map[{u, v}];
  }
  return cost;
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