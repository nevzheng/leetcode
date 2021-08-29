// 1798_max_consecutive_values_you_can_make
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * At First glance this problem looks like its a variant of the coin change
 * problem without duplicates. We can solve it this by incrementally improving
 * the max sum we can reach with the addition of each coin.
 * However, implementing it gives us a TLE.
 *
 * We can also take a greedy approach, incrementally considering the the largest
 * value we can make with each additional coin.
 * We can increment our max_val by a coin, if the coin is less than max_val.
 * it its greater, then we would be left with a gap in our number line
 * THis will take linear time and constant space
 *
 *
 * TAKEAWAY: For "Consecutive number problems" We can incrementally build a
 * max_value. by considering whether or not including a new additional number
 * would leave a gap.
 */
class Solution {
 public:
  static int getMaximumConsecutive(vector<int>& coins) {
    // Sort coins in ascending order
    std::sort(coins.begin(), coins.end());
    auto max_val = 0;              // max_reachable is 0
    for (auto c : coins) {         // Incrementally try to include each coin
      if (c > max_val + 1) break;  // Can't include this coin, would leave gap
      max_val += c;                // Increment max_reachable
    }
    return max_val + 1;  // Return # of reachable values [0...max_val]
  }
};

TEST_CASE("1798::1", "[1798]") {
  vector<int> coins{1, 3};
  const int expected = 2;
  REQUIRE(Solution::getMaximumConsecutive(coins) == expected);
}

TEST_CASE("1798::2", "[1798]") {
  vector<int> coins{1, 1, 1, 4};
  const int expected = 8;
  REQUIRE(Solution::getMaximumConsecutive(coins) == expected);
}

TEST_CASE("1798::3", "[1798]") {
  vector<int> coins{1, 4, 10, 3, 1};
  const int expected = 20;
  REQUIRE(Solution::getMaximumConsecutive(coins) == expected);
}
