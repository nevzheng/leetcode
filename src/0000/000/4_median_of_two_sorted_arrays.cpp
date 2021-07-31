// 4_median_of_two_sorted_arrays
// Nevin Zheng
// 7/30/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  double findMedianSortedArrays(const vector<int>& A, const vector<int>& B) {
    int a_len = static_cast<int>(A.size());
    int b_len = static_cast<int>(B.size());
    // Ensure that A is the smaller array
    if (b_len < a_len) return findMedianSortedArrays(B, A);
    int lo{0};
    int hi{a_len};
    while (lo <= hi) {
      int a_mid = (hi + lo) / 2;
      int b_mid = ((a_len + b_len + 1) / 2) - a_mid;
      int a_left = a_mid == 0 ? INT_MIN : A[a_mid - 1];
      int b_left = b_mid == 0 ? INT_MIN : B[b_mid - 1];
      int a_right = a_mid == a_len ? INT_MAX : A[a_mid];
      int b_right = b_mid == b_len ? INT_MAX : B[b_mid];

      if (a_left <= b_right and b_left <= a_right) {
        if ((a_len + b_len) % 2) {
          return max(a_left, b_left);
        }
        return (max(a_left, b_left) + min(a_right, b_right)) / 2.0;
      }
      if (a_left > b_right) {
        hi = a_mid - 1;
      } else {
        lo = a_mid + 1;
      }
    }
    return 0.;
  }
};

TEST_CASE("4ex1", "[4]") {
  const vector<int> a{1, 3};
  const vector<int> b{2};
  const double expected = 2.0;
  REQUIRE(Solution().findMedianSortedArrays(a, b) == expected);
}

TEST_CASE("4ex2", "[4]") {
  const vector<int> a{0, 0};
  const vector<int> b{0, 0};
  const double expected = 0.0;
  REQUIRE(Solution().findMedianSortedArrays(a, b) == expected);
}

TEST_CASE("4ex3", "[4]") {
  const vector<int> a{};
  const vector<int> b{1};
  const double expected = 1;
  REQUIRE(Solution().findMedianSortedArrays(a, b) == expected);
}

TEST_CASE("4ex4", "[4]") {
  const vector<int> a{2};
  const vector<int> b{};
  double expected = 2;
  REQUIRE(Solution().findMedianSortedArrays(a, b) == expected);
}

TEST_CASE("4ex5", "[4]") {
  const vector<int> a{1, 2};
  const vector<int> b{3, 4};
  const double expected = 2.5;
  REQUIRE(Solution().findMedianSortedArrays(a, b) == expected);
}
