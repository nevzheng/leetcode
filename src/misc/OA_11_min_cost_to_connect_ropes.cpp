// OA_11_min_cost_to_connect_ropes
// Nevin Zheng
// 8/10/21
// https://github.com/Zhouzhiling/leetcode/blob/master/Amazon.%20Min%20Cost%20to%20Connect%20Ropes.md
// leetcode min cost to connect sticks

// Given n ropes of different lengths, we need to connect these ropes into one
// rope. We can connect only 2 ropes at a time. The cost required to connect 2
// ropes is equal to sum of their lengths. The length of this connected rope is
// also equal to the sum of their lengths. This process is repeated until n
// ropes are connected into a single rope. Find the min possible cost required
// to connect all ropes.

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

int minCost(const vector<int>& ropes) {
  int cost = 0;
  // O(N) time and space
  priority_queue pq(std::greater(), ropes);  // Min Heapify, O(N) Spe + Tme
  // There will be O(N) pops and each is O(N) time
  // O(NLgN) + O(N) space
  while (pq.size() >= 2) {
    auto x = pq.top();
    pq.pop();
    auto y = pq.top();
    pq.pop();
    cost += x + y;
    pq.push(x + y);
  }
  return cost;
}

TEST_CASE("OA::11::1", "[oa11]") {
  const vector<int> ropes = {8, 4, 6, 12};
  const auto expected = 58;
  REQUIRE(minCost(ropes) == expected);
}

TEST_CASE("OA::11::2", "[oa11]") {
  const vector<int> ropes = {20, 4, 8, 2};
  const auto expected = 54;
  REQUIRE(minCost(ropes) == expected);
}

TEST_CASE("OA::11::3", "[oa11]") {
  const vector<int> ropes = {1, 2, 5, 10, 35, 89};
  const auto expected = 224;
  REQUIRE(minCost(ropes) == expected);
}

TEST_CASE("OA::11::4", "[oa11]") {
  const vector<int> ropes = {2, 2, 3, 3};
  const auto expected = 20;
  REQUIRE(minCost(ropes) == expected);
}
