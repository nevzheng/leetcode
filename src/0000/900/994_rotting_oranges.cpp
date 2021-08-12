// 994_rotting_oranges
// Nevin Zheng
// 8/11/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We'll apply a BFS/Level Order Traversal
 *
 * Each Orange will be visited at most once. Worst case is whole grid
 * has oranges. O(NM) time and space
 */
using Position = pair<int, int>;
class Solution {
 public:
  static constexpr int kFresh = 1;
  static constexpr int kRotten = 2;

  const vector<Position> kDelta = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  int orangesRotting(const vector<vector<int>>& grid) {
    int m = static_cast<int>(grid.size());
    int n = static_cast<int>(grid.front().size());
    set<Position> fresh;
    queue<Position> q;
    vector visited(m, vector(n, false));
    for (auto i = 0; i < m; i++) {
      for (auto j = 0; j < n; j++) {
        if (grid[i][j] == kRotten) q.emplace(i, j);
        if (grid[i][j] == kFresh) fresh.emplace(i, j);
      }
    }
    if (fresh.empty()) return 0;  // Edge Case No Fresh oranges in beginning
    int depth = 0;
    while (!fresh.empty() && !q.empty()) {
      auto count = q.size();
      while (count--) {
        auto cur = q.front();
        q.pop();
        // Mark visited
        visited[cur.first][cur.second] = true;
        // Remove cur from fresh if exists
        if (auto it = fresh.find(cur); it != fresh.end()) {
          fresh.erase(it);
        }
        // Push Neighbors onto Queue
        for (const auto& [dx, dy] : kDelta) {
          auto nx = cur.first + dx;
          auto ny = cur.second + dy;
          if (0 <= nx and nx < m and 0 <= ny and ny < n and !visited[nx][ny] and
              grid[nx][ny] == kFresh)
            q.emplace(nx, ny);
        }
      }
      ++depth;
    }
    return fresh.empty() ? depth - 1 : -1;
  }
};

TEST_CASE("994::1", "[994]") {
  const vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  const auto expected = 4;
  REQUIRE(Solution().orangesRotting(grid) == expected);
}

TEST_CASE("994::2", "[994]") {
  const vector<vector<int>> grid = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
  const auto expected = -1;
  REQUIRE(Solution().orangesRotting(grid) == expected);
}

TEST_CASE("994::3", "[994]") {
  const vector<vector<int>> grid = {{0, 2}};
  const auto expected = 0;
  REQUIRE(Solution().orangesRotting(grid) == expected);
}
