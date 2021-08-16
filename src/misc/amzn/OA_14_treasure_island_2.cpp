// OA_14_treasure_island_2
// Nevin Zheng
// 8/10/21

// https://github.com/Zhouzhiling/leetcode/blob/master/Amazon.%20Treasure%20Island%20II.md

/**
 You have a map that marks the locations of treasure islands. Some of the map
area has jagged rocks and dangerous reefs. Other areas are safe to sail in.
There are other explorers trying to find the treasure. So you must figure out a
shortest route to one of the treasure islands.

Assume the map area is a two dimensional grid, represented by a matrix of
characters. You must start from one of the starting point (marked as S) of the
map and can move one block up, down, left or right at a time. The treasure
island is marked as X. Any block with dangerous rocks or reefs will be marked as
D. You must not enter dangerous blocks. You cannot leave the map area. Other
areas O are safe to sail in. Output the minimum number of steps to get to any of
the treasure islands.
 */

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

struct Position {
  int x;
  int y;
};

/**
 * We will do a 2 pass DP to minimize the distances of dp[i][j] which
 * represent the distance to the nearest X treasure
 * O(mn) space and time
 * @param map
 * @return
 */
int treasureIslandII(vector<vector<char>>& map) {
  int m = static_cast<int>(map.size());
  int n = static_cast<int>(map.front().size());

  // need large number no overflow
  // dp[i][j] = distance from nearest treasure X square
  vector dp(m, vector(n, INT_MAX));
  // Locate all starting points and store them
  // O(MN) Time and O(Start) space
  vector<Position> starts;
  // First Pass Top Left to Bottom Right
  for (auto i = 0; i < m; ++i) {
    for (auto j = 0; j < n; ++j) {
      // Only in this loop, record the starts
      if (map[i][j] == 'S') starts.push_back({i, j});

      if (map[i][j] == 'X') {
        dp[i][j] = 0;
      } else if (map[i][j] == 'D') {
        dp[i][j] = INT_MAX;
      } else {
        auto top = i - 1 > 0 ? dp[i - 1][j] : INT_MAX;
        auto left = j - 1 > 0 ? dp[i][j - 1] : INT_MAX;
        dp[i][j] = min(top, left) != INT_MAX ? 1 + min(top, left) : INT_MAX;
      }
    }
  }

  // Second Pass Bottom right to Top Left
  for (auto i = m - 1; i >= 0; --i) {
    for (auto j = n - 1; j >= 0; --j) {
      if (map[i][j] == 'X') {
        dp[i][j] = 0;
      } else if (map[i][j] == 'D') {
        dp[i][j] = INT_MAX;
      } else {
        auto bottom = i + 1 < m ? dp[i + 1][j] : INT_MAX;
        auto right = j + 1 < n ? dp[i][j + 1] : INT_MAX;
        dp[i][j] =
            min(bottom, right) != INT_MAX ? 1 + min(bottom, right) : INT_MAX;
      }
    }
  }

  // Find the min distance among all Starts
  // O(Start) time
  auto min_dist = INT_MAX;
  for (const auto& s : starts) {
    min_dist = min(min_dist, dp[s.x][s.y]);
  }
  return min_dist;
}

TEST_CASE("OA::14::1", "[oa14]") {
  vector<vector<char>> map = {{'S', 'O', 'O', 'S', 'S'},
                              {'D', 'O', 'D', 'O', 'D'},
                              {'O', 'O', 'O', 'O', 'X'},
                              {'X', 'D', 'D', 'O', 'O'},
                              {'X', 'D', 'D', 'D', 'O'}};
  const auto expected = 3;
  REQUIRE(treasureIslandII(map) == expected);
}