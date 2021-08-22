// 329_longest_increasing_path_in_a_matrix
// Nevin Zheng
// 8/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We can formulate the problem in to finding the longest path in a DAG
 * We will imagine each tile as a node in the graph. A directed edge will be
 * drawn if the tiles are adjacent and FROM is less than TO.
 *
 *
 * To implement we will assign an id to each tile. make an adjacency list
 * and perform a topological sort. We'll use khan's algorithm
 * this will take O(MN) time and space
 */
class Solution {
 public:
  constexpr static array<tuple<int, int>, 4> kDirections{
      {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};

  static int longestIncreasingPath(const vector<vector<int>>& matrix) {
    if (matrix.empty()) return 0;
    auto r = static_cast<int>(matrix.size());
    auto c = static_cast<int>(matrix.front().size());
    vector<vector<int>> in_degree(r, vector<int>(c));
    queue<pair<int, int>> zero_degree;
    for (auto i = 0; i < r; ++i) {
      for (auto j = 0; j < c; ++j) {
        for (const auto& [dx, dy] : kDirections) {
          auto nx = i + dx;
          auto ny = j + dy;
          if (0 <= nx && nx < r && 0 <= ny && ny < c &&
              matrix[i][j] < matrix[nx][ny])
            ++in_degree[nx][ny];
        }
      }
    }

    for (auto i = 0; i < r; ++i)
      for (auto j = 0; j < c; ++j)
        if (in_degree[i][j] == 0) zero_degree.emplace(i, j);

    auto path_len = 0;
    while (!zero_degree.empty()) {
      auto sz = zero_degree.size();
      while (sz--) {
        auto [x, y] = zero_degree.front();
        zero_degree.pop();
        for (const auto& [dx, dy] : kDirections) {
          auto nx = x + dx;
          auto ny = y + dy;
          if (0 <= nx && nx < r && 0 <= ny && ny < c &&
              matrix[nx][ny] > matrix[x][y] && --in_degree[nx][ny] == 0)
            zero_degree.emplace(nx, ny);
        }
      }
      ++path_len;
    }
    return path_len;
  }
};

TEST_CASE("329::1", "[329]") {
  const vector<vector<int>> matrix = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};
  auto expected = 4;
  REQUIRE(Solution().longestIncreasingPath(matrix) == expected);
}

TEST_CASE("329::2", "[329]") {
  const vector<vector<int>> matrix = {{0}, {1}, {5}, {5}};
  auto expected = 3;
  REQUIRE(Solution().longestIncreasingPath(matrix) == expected);
}