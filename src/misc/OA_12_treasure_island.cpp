// OA_12_treasure_island
// Nevin Zheng
// 8/10/21

// https://github.com/Zhouzhiling/leetcode/blob/master/Amazon.%20Treasure%20Island.md

// You have a map that marks the location of a treasure island. Some map
// areas have jagged rocks and dangerous reefs. Other areas are safe to sail in.
// There are other explorers trying to find the treasure. So you must figure out
// the shortest route to the treasure island.
//
// Assume the map area is a two-dimensional grid, represented by a matrix of
// characters. You must start from the top-left corner of the map and can move
// one block up, down, left or right at a time. The treasure island is marked as
// X in a block of the matrix. X will not be in the top-left corner. Any block
// with dangerous rocks or reefs will be marked as D. You must not enter
// dangerous blocks. You cannot leave the map area. Other areas O are safe to
// sail in. The top-left corner is always safe. Output the minimum number of
// steps to get to the treasure.

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

struct Position {
  int x;
  int y;
};

bool validBounds(int m, int n, int x, int y) {
  return (0 <= x and x < m and 0 <= y and y < n);
}
/**
 * We'll perform a BFS to find the treasure island. Only valid squares will
 * be added to the bfs queue.
 * In the worst case we'll visit all squares once thus.
 * O(N^2) time and O(N^2) space.
 *
 * @param map
 * @return
 */
int treasureIsland(vector<vector<char>>& map) {
  static const vector<Position> kDelta = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  auto m = static_cast<int>(map.size());
  auto n = static_cast<int>(map.front().size());
  vector visited(m, vector(n, false));
  queue<Position> q{{{0, 0}}};
  auto depth = 0;
  while (!q.empty()) {
    auto level_count = q.size();
    while (level_count--) {
      auto [x, y] = q.front();
      q.pop();
      visited[x][y] = true;
      if (map[x][y] == 'X') return depth;  // Found, Exit
      for (const auto& d : kDelta) {       // Push Neighbors
        auto a = x + d.x;
        auto b = y + d.y;
        if (validBounds(m, n, a, b) and !visited[a][b] and map[a][b] != 'D') {
          q.push({a, b});
        }
      }
    }
    ++depth;
  }
  return -1;  // We visited all possible squares and didn't find X
}

TEST_CASE("ex1", "[]") {
  vector<vector<char>> map = {{'O', 'O', 'O', 'O'},
                              {'D', 'O', 'D', 'O'},
                              {'O', 'O', 'O', 'O'},
                              {'X', 'D', 'D', 'O'}};
  const auto expected = 5;
  REQUIRE(treasureIsland(map) == expected);
}