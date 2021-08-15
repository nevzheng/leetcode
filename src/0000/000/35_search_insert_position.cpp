// 35_search_insert_position
// Nevin Zheng
// 8/14/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    return std::distance(nums.begin(),
                         std::lower_bound(nums.begin(), nums.end(), target));
  }
};

TEST_CASE("35::1", "[35]") {
  auto input = {};
  auto expected = {};
  REQUIRE(Solution().foo(input) == expected);
}