// 330_patching_array
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We will apply an incremental greedy algorithm that gradually increases the
 * maximum value reachable with values in [0..idx] as well as any values we add
 * take [1,5,10] as an example
 * we start w/ the empty array, which has a max val of zero
 * we add 1, increasing our max number to 1
 * we can't add 5 immediately because that would cause a gap.
 * So we need to add our max_num+1 to our working set giving us [1,2,| 5,10]
 * where the bar indicates up to where we have considered so far
 * our max val, then goes from 1 to three or max_val + (max_val +1) = 3
 * The max vali in our working set adds to 3.
 * In our next iteration, we attempt to consider adding to our working set, but
 * can't, because that would exclude 4. Thus we need to add 3 to our WS.
 * max_num += max_num+1 = 6. 1,2,3 => max_sum = 6
 * Next round, we can include 5. leaving us with a max_sum of 11
 * 1,2,3,5
 * Next round we add 10. leaving us with a max sum of 21
 * 1,2,3,5,10
 *
 */
class Solution {
 public:
  static int minPatches(const vector<int>& nums, int tgt) {
    int cnt = 0;
    auto i = 0UL;
    auto max_num = 0LL;
    while (max_num < tgt) {  // Iterate we meet tgt
      // Can we include current idx, w/o gaps
      if (i < nums.size() && nums[i] <= max_num + 1) {
        max_num += nums[i++];
      } else {  // Need to patch
        max_num += max_num + 1;
        cnt++;  // Increment count of patched numbers
      }
    }
    return cnt;
  }
};

TEST_CASE("330::1", "[330]") {
  const vector<int> nums{1, 3};
  const auto n = 6;
  const auto expected = 1;
  REQUIRE(Solution::minPatches(nums, n) == expected);
}

TEST_CASE("330::2", "[330]") {
  const vector<int> nums{1, 5, 10};
  const auto n = 20;
  const auto expected = 2;
  REQUIRE(Solution::minPatches(nums, n) == expected);
}

TEST_CASE("330::4", "[330]") {
  const vector<int> nums{1, 2, 2};
  const auto n = 5;
  const auto expected = 0;
  REQUIRE(Solution::minPatches(nums, n) == expected);
}