// 1046_last_stone_weight
// Nevin Zheng
// 8/3/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int lastStoneWeight(const vector<int>& stones) {
    std::priority_queue pq(less<>(), stones);  // Heapify O(n)
    while (pq.size() >= 2) {
      auto x = pq.top();
      pq.pop();
      auto y = pq.top();
      pq.pop();
      if (x != y) pq.push(abs(x - y));
    }
    return pq.empty() ? 0 : pq.top();
  }
};

TEST_CASE("1046ex1", "[1046]") {
  const vector<int> input = {2, 7, 4, 1, 8, 1};
  const int expected = 1;
  REQUIRE(Solution::lastStoneWeight(input) == expected);
}