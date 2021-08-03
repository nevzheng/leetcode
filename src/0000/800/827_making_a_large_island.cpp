// 827_making_a_large_island
// Nevin Zheng
// 8/1/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class UnionFind {
 public:
  vector<int> id_;
  vector<int> size_;

  explicit UnionFind(int n) : id_(n), size_(n, 1) {
    std::iota(id_.begin(), id_.end(), 0);
  }

  /**
   * Return the Size of a set
   * @param u
   * @return
   */
  int size(int u) { return size_[find(u)]; }

  /**
   * Find the root node of an index
   * @return
   */
  int find(int p) {
    auto root = p;
    while (root != id_[root]) root = id_[root];
    while (p != root) {  // Do Path Compression
      auto next = id_[p];
      id_[p] = root;
      p = next;
    }
    return root;
  }

  /**
   * Return a Tuple Containing (set, size) of a given node
   * @param u
   * @return
   */
  pair<int, int> info(int u) { return {find(u), size(u)}; }

  void unite(int p, int q) {
    auto p_root = find(p);
    auto q_root = find(q);
    if (p_root == q_root) return;
    if (size_[p_root] < size_[q_root]) {
      size_[q_root] += size_[p_root];
      id_[p_root] = q_root;
    } else {
      size_[p_root] += size_[q_root];
      id_[q_root] = p_root;
    }
  }
};

// X, Y coordinate
using Position = pair<int, int>;
class Solution {
 public:
  int largestIsland(const vector<vector<int>>& grid) {
    auto len = static_cast<int>(grid.size());
    map<Position, int> ones;  // Map of ones coord to index
    vector<Position> zeros;   // Position of zeros in grid;
    for (auto i = 0; i < len; i++) {
      for (auto j = 0; j < len; j++) {
        if (grid[i][j] == 0) {
          zeros.emplace_back(i, j);
        } else {
          ones[{i, j}] = static_cast<int>(ones.size());
        }
      }
    }

    // No zeros to flip
    if (zeros.empty()) return static_cast<int>(ones.size());

    const static vector<Position> kDeltas = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    // Create a union find for all the ones
    UnionFind uf(static_cast<int>(ones.size()));
    // Do an initial pass to find the number and size of each island

    for (const auto& o : ones) {
      auto [ox, oy] = o.first;  // Get the index of the one
      int o_id = o.second;
      for (const auto& [dx, dy] : kDeltas) {
        if ((0 <= ox + dx) && (ox + dx < len) && (0 <= oy + dy) &&
            (oy + dy < len) && grid[ox + dx][oy + dy] == 1) {
          uf.unite(o_id, ones.at({ox + dx, oy + dy}));
        }
      }
    }

    auto max_size = INT_MIN;
    // For Each Zero check the size of the island it would make
    for (const auto& [zx, zy] : zeros) {
      auto size = 1;  // Size if zero is flipped
      set<int> seen;
      for (auto [dx, dy] : kDeltas) {
        if (auto it = ones.find({zx + dx, zy + dy}); it != end(ones)) {
          auto [id, sz] = uf.info(it->second);
          if (!seen.count(id)) size += sz;
          seen.insert(id);
        }
      }
      max_size = max(max_size, size);
    }
    return max_size;
  }
};

TEST_CASE("827ex1", "[827]") {
  const vector<vector<int>> grid{{1, 0}, {0, 1}};
  const int expected = 3;
  REQUIRE(Solution().largestIsland(grid) == expected);
}

TEST_CASE("827ex2", "[827]") {
  const vector<vector<int>> grid{{1, 1}, {1, 0}};
  const int expected = 4;
  REQUIRE(Solution().largestIsland(grid) == expected);
}

TEST_CASE("827ex3", "[827]") {
  const vector<vector<int>> grid{{1, 1}, {1, 1}};
  const int expected = 4;
  REQUIRE(Solution().largestIsland(grid) == expected);
}

TEST_CASE("827ex4", "[827]") {
  const vector<vector<int>> grid{{0, 0}, {1, 1}};
  const int expected = 3;
  REQUIRE(Solution().largestIsland(grid) == expected);
}

TEST_CASE("827ex5", "[827]") {
  const vector<vector<int>> grid = {{0, 0, 0, 0, 0, 0, 0},  // align w/ comment
                                    {0, 1, 1, 1, 1, 0, 0},  //
                                    {0, 1, 0, 0, 1, 0, 0},  //
                                    {1, 0, 1, 0, 1, 0, 0},  //
                                    {0, 1, 0, 0, 1, 0, 0},  //
                                    {0, 1, 0, 0, 1, 0, 0},  //
                                    {0, 1, 1, 1, 1, 0, 0}};
  const int expected = 18;
  REQUIRE(Solution().largestIsland(grid) == expected);
}
