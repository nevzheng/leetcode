// min_cost_to_repair_edges
// https://leetcode.com/discuss/interview-question/357310
// Nevin Zheng
// 7/23/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;
/**
 *
 * @param n_vertices Total number of nodes
 * @param edges List of integre pairs representin the nodes connected by an edge
 * @param edgesToRepair A list where each element is a triplet representing
 * the pair of nodes between which an ides is currently broken and the cost
 * of repairing that edge [u,v,cost] = [1,2,12]
 * @return Minimum Cost to fully connect the graph
 */
int costToRepair(int n_vertices, const vector<vector<int>>& edges,
                 const vector<vector<int>>& edgesToRepair) {}

TEST_CASE("costToRepairEx1", "[costToRepair]") {
  // Input: n = 5,
  // edges = [[1, 2], [2, 3], [3, 4], [4, 5], [1, 5]],
  // edgesToRepair = [[1, 2, 12], [3, 4, 30], [1, 5, 8]]
  // Output: 20
  // Explanation:
  // There are 3 connected components due to broken edges: [1], [2, 3] and [4,
  // 5]. We can connect these components into a single component by repearing
  // the edges between nodes 1 and 2, and nodes 1 and 5 at a minimum cost 12 + 8
  // = 20.
  const auto n = 5;
  const vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}};
  const vector<vector<int>> edges_to_repair = {
      {1, 2, 12}, {3, 4, 30}, {1, 5, 8}};
  const auto expected = 20;
  REQUIRE(costToRepair(n, edges, edges_to_repair) == expected);
}

TEST_CASE("costToRepairEx2", "[costToRepair]") {
  const auto n = 6;
  const vector<vector<int>> edges = {{1, 2}, {2, 3}, {4, 5},
                                     {3, 5}, {1, 6}, {2, 4}};
  const vector<vector<int>> edges_to_repair = {{1, 6, 410}, {2, 4, 800}};
  const auto expected = 410;
  REQUIRE(costToRepair(n, edges, edges_to_repair) == expected);
}

TEST_CASE("costToRepairEx3", "[costToRepair]") {
  const auto n = 6;
  const vector<vector<int>> edges = {{1, 2}, {2, 3}, {4, 5}, {5, 6},
                                     {1, 5}, {2, 4}, {3, 4}};
  const vector<vector<int>> edges_to_repair = {
      {1, 5, 110}, {2, 4, 84}, {3, 4, 79}};
  const auto expected = 79;
  REQUIRE(costToRepair(n, edges, edges_to_repair) == expected);
}