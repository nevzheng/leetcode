// 565_array_nesting
// Nevin Zheng
// 9/1/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * Lets assume we're brute forcing the solution. We basically add elements
 * until we see an element that's already been added
 * In other words we're traversing a graph and detecting a cycle.
 * We also note that any number on a cycle will "represent" the cycle, and all
 * indices on a cycle will have the same max len which means that
 * traversing it again can't improve the answer.
 * Thus we can traverse cycles, marking each node as visited until all cycles
 * have been explored, taking the max len of each cycle.
 */
class Solution {
 public:
  static int arrayNesting(vector<int>& nums) {
    auto ans = 0;
    for (auto i = 0; i < static_cast<int>(nums.size()); ++i) {
      if (nums[i] != INT_MAX) {
        auto start = nums[i];
        auto count = 0;
        fmt::print("start {}\n", start);
        while (nums[start] != INT_MAX) {
          auto tmp = start;
          start = nums[start];
          ++count;
          nums[tmp] = INT_MAX;
        }
        ans = max(ans, count);
      }
    }
    return ans;
  }
};

TEST_CASE("565::1", "[565]") {
  vector<int> nums{5, 4, 0, 3, 1, 6, 2};
  const auto expected = 4;
  REQUIRE(Solution::arrayNesting(nums) == expected);
}