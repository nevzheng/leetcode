// 223_rectangle_area
// Nevin Zheng
// 8/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/*
 * There are a few cases for area of two rectangles on a plane.
 * i.  Disjoint, no overlap: Sum both areas
 * ii. Intersecting. Sum Areas, subtract overlap
 * In either case the area is given by A + B - (A U B)
 * The key to the question is how we can compute the overlapping portion of the
 * rectangle if it exists.
 */
class Solution {
 public:
  static int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1,
                         int bx2, int by2) {
    auto area1 = (ax2 - ax1) * (ay2 - ay1);  // Find the area of rectangle A.
    auto area2 = (bx2 - bx1) * (by2 - by1);  // Find the area of rectangle B.
    // Check the condition if both the rectangles overlap or not.
    if ((ay1 >= by2) || (ax2 <= bx1) || (ax1 >= bx2) || (by1 >= ay2)) {
      return area1 + area2;
    }
    auto cx1 = max(ax1, bx1);
    auto cy1 = max(ay1, by1);
    auto cx2 = min(ax2, bx2);
    auto cy2 = min(by2, ay2);
    auto ab_area = (cx2 - cx1) * (cy2 - cy1);
    return area1 + area2 - ab_area;
  }
};

TEST_CASE("223::1", "[223]") {
  const auto ax1 = -3;
  const auto ay1 = 0;
  const auto ax2 = 3;
  const auto ay2 = 4;
  const auto bx1 = 0;
  const auto by1 = -1;
  const auto bx2 = 9;
  const auto by2 = 2;
  const auto expected = 45;
  REQUIRE(Solution::computeArea(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2) ==
          expected);
}

TEST_CASE("223::2", "[223]") {
  const auto ax1 = -2;
  const auto ay1 = -2;
  const auto ax2 = 2;
  const auto ay2 = 2;
  const auto bx1 = -2;
  const auto by1 = -2;
  const auto bx2 = 2;
  const auto by2 = 2;
  const auto expected = 16;
  REQUIRE(Solution::computeArea(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2) ==
          expected);
}