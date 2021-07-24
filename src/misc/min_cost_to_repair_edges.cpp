// min_cost_to_repair_edges
// https://leetcode.com/discuss/interview-question/357310
// Nevin Zheng
// 7/23/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <utility>

using namespace std;

class UnionFind {
 private:
  vector<int> ids_;
  vector<int> sizes_;

 public:
  /**
   * Construct a UnionFind initialized with n elements in n distinct sets
   * @param n
   */
  explicit UnionFind(int n) : ids_(vector<int>(n)), sizes_(n, 1) {
    iota(begin(ids_), end(ids_), 0);
  }

  /**
   * Return which root of the component that p belongs to
   * Follows the tree until a root node is found and returned
   * @param p
   * @return
   */
  int find(int p) {
    auto root = p;
    while (root != ids_[root]) root = ids_[root];

    while (p != ids_[p]) {  // Perform Path Compression
      auto next = ids_[p];
      ids_[p] = root;
      p = next;
    }
    return root;
  }

  /**
   * Return the size of the component that p belongs to
   * @param p
   * @return
   */
  int size(int p) { return sizes_[find(p)]; }

  /**
   * Determine if p and q belong to the same component
   * @param p
   * @param q
   * @return true if p and q are in the same component. Else False.
   */
  bool connected(int p, int q) { return find(p) == find(q); }

  /**
   * Unite components p and q
   * Uses Union by Rank to limit height of trees
   * @param p
   * @param q
   */
  void unite(int p, int q) {
    auto p_root = find(p);
    auto q_root = find(q);
    if (sizes_[p_root] < sizes_[q_root]) {
      sizes_[q_root] += sizes_[p_root];
      ids_[p_root] = q_root;
    } else {
      sizes_[p_root] += sizes_[q_root];
      ids_[q_root] = p_root;
    }
  }
};

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
                 const vector<vector<int>>& edgesToRepair) {
  auto min_cost = 0;
  // Create a set indicating broken edges. Good For fast lookup
  set<pair<int, int>> broken_edges;
  for (const auto& e : edgesToRepair) {
    broken_edges.emplace(e[0] - 1, e[1] - 1);
    broken_edges.emplace(e[1] - 1, e[0] - 1);
  }
  // Vec of edges for kruskal's algo
  // Cost, U, V
  vector<tuple<int, int, int>> edge_vec;
  // add Edges with zero cost representing unbroken edges
  for (auto e : edges) {
    if (broken_edges.count({e[0] - 1, e[1] - 1}) == 0U) {
      edge_vec.emplace_back(0, e[0] - 1, e[1] - 1);
      edge_vec.emplace_back(0, e[1] - 1, e[0] - 1);
    }
  }
  // Add Broken Edges into to the edge ved
  transform(begin(edgesToRepair), end(edgesToRepair), back_inserter(edge_vec),
            [](const auto e) { return make_tuple(e[2], e[0] - 1, e[1] - 1); });

  // Sort the edge vector by Cost, default is compare by first index
  sort(begin(edge_vec), end(edge_vec));
  // create unionfind for kruskals
  UnionFind uf(n_vertices);
  for (auto& e : edge_vec) {
    auto [w, u, v] = e;
    if (uf.connected(u, v)) continue;  // Avoid Cycles
    min_cost += w;
    uf.unite(u, v);
    if (uf.size(0) == n_vertices) break;
  }
  if (uf.size(0) != n_vertices) return -1;
  return min_cost;
}

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