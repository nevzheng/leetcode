// 1306_jump_game_iii.cpp
// Nevin Zheng
// 7/27/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

bool dfs(const vector<int>& A, vector<bool>& visited, int root) {
  if (visited[root]) return false;  // Skip Processed Nodes
  if (A[root] == 0) return true;    // Return on finding 0
  visited[root] = true;             // Mark Visited to avoid cycles
  if (0 <= root - A[root] and dfs(A, visited, root - A[root])) {
    return true;
  }
  if (root + A[root] < static_cast<int>(A.size()) and
      dfs(A, visited, root + A[root])) {
    return true;
  }
  return false;  // Exit
}

bool canReach(const vector<int>& A, int start) {
  vector<bool> visited(A.size());
  return dfs(A, visited, start);
}

TEST_CASE("1306ex1", "[1306]") {
  const vector<int> arr = {4, 2, 3, 0, 3, 1, 2};
  const auto start = 5;
  const auto expected = true;
  REQUIRE(canReach(arr, start) == expected);
}
TEST_CASE("1306ex2", "[1306]") {
  const vector<int> arr = {4, 2, 3, 0, 3, 1, 2};
  const auto start = 0;
  const auto expected = true;
  REQUIRE(canReach(arr, start) == expected);
}
TEST_CASE("1306ex3", "[1306]") {
  const vector<int> arr = {3, 0, 2, 1, 2};
  const auto start = 2;
  const auto expected = false;
  REQUIRE(canReach(arr, start) == expected);
}