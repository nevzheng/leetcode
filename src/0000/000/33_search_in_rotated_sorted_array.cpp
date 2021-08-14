// 33_search_in_rotated_sorted_array
// Nevin Zheng
// 7/31/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int search(const vector<int>& A, int tgt) {
    auto lo = 0UL;
    auto hi = A.size() - 1;
    while (lo <= hi) {
      auto mid = lo + ((hi - lo) / 2);
      if (A[mid] == tgt) return static_cast<int>(mid);
      if (A[lo] <= A[mid]) {                  // Left Half Is Sorted
        if (A[lo] <= tgt and tgt < A[mid]) {  // Search left sorted portion
          hi = mid - 1;
        } else {  // Not in sorted portion check unsorted
          lo = mid + 1;
        }
      } else if (A[mid] <= A[hi]) {           // right Half is sorted
        if (A[mid] <= tgt and tgt < A[hi]) {  // Check right sorted portion
          lo = mid + 1;
        } else {
          hi = mid - 1;  // Not in right sorted, check left
        }
      }
    }
    return -1;
  }
};

TEST_CASE("33ex1", "[33]") {
  const vector nums{4, 5, 6, 7, 0, 1, 2};
  const auto target = 0;
  const auto expected = 4;
  REQUIRE(Solution::search(nums, target) == expected);
}

TEST_CASE("33ex2", "[33]") {
  const vector nums{4, 5, 6, 7, 0, 1, 2};
  const auto target = 3;
  const auto expected = -1;
  REQUIRE(Solution::search(nums, target) == expected);
}

TEST_CASE("33ex3", "[33]") {
  const vector nums{0};
  const auto target = 1;
  const auto expected = -1;
  REQUIRE(Solution::search(nums, target) == expected);
}