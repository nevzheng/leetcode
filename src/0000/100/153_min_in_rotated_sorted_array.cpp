// 153_min_in_rotated_sorted_array
// Nevin Zheng
// 8/31/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * Visualize the array as first a monotonically increasing, then dropping
 * to a minimum and then monotonically increasing again.
 * The point where the transition occurs is a pivot.
 * The array is mostly sorted, so we can apply binary search to locate the pivot
 * IE an index s.t.  A[ pivot - 1 ] > A[pivot]
 */
class Solution {
 public:
  static int findMin(const vector<int>& A) {
    auto lo = 0UL;
    auto hi = A.size() - 1;
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (A[mid] < A[hi]) {  // A[mid..hi] increasing
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    return A[lo];
  }
};

TEST_CASE("153::1", "[13]") {
  const vector<int> nums{3, 4, 5, 1, 2};
  const auto expected = 1;
  REQUIRE(Solution::findMin(nums) == expected);
}

TEST_CASE("153::2", "[13]") {
  const vector<int> nums{4, 5, 6, 7, 0, 1, 2};
  const auto expected = 0;
  REQUIRE(Solution::findMin(nums) == expected);
}

TEST_CASE("153::3", "[13]") {
  const vector<int> nums{11, 13, 15, 17};
  const auto expected = 11;
  REQUIRE(Solution::findMin(nums) == expected);
}

TEST_CASE("153::4", "[13]") {
  const vector<int> nums{0, 1, 2, 3, 4, 5, 6, 7};
  const auto expected = 0;
  REQUIRE(Solution::findMin(nums) == expected);
}

TEST_CASE("153::5", "[13]") {
  const vector<int> nums{2, 1};
  const auto expected = 1;
  REQUIRE(Solution::findMin(nums) == expected);
}
