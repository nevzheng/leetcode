// 278_first_bad_version
// Nevin Zheng
// 8/28/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// The API isBadVersion is defined for you.
bool isBadVersion(int version);

class Solution {
 public:
  static int firstBadVersion(int n) {
    auto lo = 0;
    auto hi = n;
    while (lo <= hi) {
      // We Need to Find Two Elements
      // mid && mid+1, s.t mid is Good and Mid+1 is Bad
      // IE Last Good Version and First Bad Version
      auto mid = lo + ((hi - lo) / 2);
      if (!isBadVersion(mid) && isBadVersion(mid + 1)) return mid + 1;
      if (!isBadVersion(mid) && !isBadVersion(mid + 1)) {
        lo = mid + 1;  // Both Good Go Higher
      } else {
        hi = mid - 1;  // Both Bad Go Lower
      }
    }
    return -1;
  }
};

TEST_CASE("278::1", "[278]") {
  const auto n = 5;
  const auto expected = 4;
  REQUIRE(Solution::firstBadVersion(n) == expected);
}