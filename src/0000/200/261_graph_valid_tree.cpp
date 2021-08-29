// 261_graph_valid_tree
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * There are several equivalent definitions for a tree.
 * A tree with N finitely many vertices will have N-1 edges
 * A Tree is connected and acyclic
 *
 * n-1 is guaranteed by the constraints. We just need to count the
 * number of components and determine if the graph has a cycle
 */
class Solution {
 public:
  enum class Color {
    kWhite,  // Unvisited
    kGray,   // Processing
    kBlack   // Visited
  };

  /**
   * Returns whether or not a graph is acyclic using a 3 Color DFS algorithm
   * @param n
   * @param edges
   * @param colors
   * @param idx
   * @return
   */
  static bool isAcyclic(int n, const vector<vector<int>>& edges,
                        vector<Color>& colors, int idx) {
    if (colors[idx] == Color::kBlack) return true;  // Visited
    if (colors[idx] == Color::kGray) return false;  // Cycle
    colors[idx] = Color::kGray;                     // Mark Processing
    if (std::any_of(edges.begin(), edges.end(), [&](auto& e) {
          return e[0] == idx && !isAcyclic(n, edges, colors, e[1]);
        }))
      return false;
    colors[idx] = Color::kBlack;  // Mark Visited
    return true;
  }

  static bool validTree(int n, const vector<vector<int>>& edges) {
    vector<Color> colors(n, Color::kWhite);
    // isAcyclic && Connected
    return isAcyclic(n, edges, colors, 0) ||
           std::all_of(colors.begin(), colors.end(),
                       [](auto c) { return c == Color::kBlack; });
  }
};

TEST_CASE("261::1", "[261]") {
  const auto n = 5;
  const vector<vector<int>> edges{{0, 1}, {0, 2}, {0, 3}, {1, 4}};
  auto expected = true;
  REQUIRE(Solution::validTree(n, edges) == expected);
}

TEST_CASE("261::2", "[261]") {
  const auto n = 5;
  const vector<vector<int>> edges{{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}};
  auto expected = true;
  REQUIRE(Solution::validTree(n, edges) == expected);
}