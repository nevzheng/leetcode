// 84_largest_rectangle_in_histogram
// Nevin Zheng
// 8/21/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * Here is a description of a naive approach, as well as how it can be
 * optimized. We can imagine, building a rectangle for each bar. We can look to
 * the left and right and keep adding a unit of width if the additional bar is
 * tall enough For N bars, you'll need to examine up to N bars. This will take
 * O(N^2) memory and O(1) space.
 *
 * We can optimize this with the use of a monotonic stack which is a variant
 * of a stack that only stores element in monotonically increasing order.
 * It will enable us to efficiently find the element less than the current bar's
 * value.
 * The Rules will be:
 * Pop while the current bar is greater that others
 * Record the position of the extend of the current bar
 * or 0 if the stack is empty.
 * Push the current index onto stack
 *
 * We will do this for both the left and right indices to find the left and
 * right extents. When we do the right traversal if the stack is empty
 * we'll push len-1
 *
 * We can then compute the area of each rectangle as H[i]*(R[i]-L[i]);
 *
 * Finding the left extent is O(n) time O(n) space
 * Finding the right extent is O(n) time O(n) space
 * Computing the areas and finding the max will take O(n) time
 */
class Solution {
 public:
  static int largestRectangleArea(const vector<int>& heights) {
    auto len = static_cast<int>(heights.size());
    vector<int> l_max(len);
    vector<int> r_max(len);
    // Store indices of element in increasing order, monotonic stack
    stack<int> stk;

    for (auto i = 0; i < len; ++i) {
      // Pop until the stk is empty or top is less than heights[i]
      while (!stk.empty() && heights[stk.top()] >= heights[i]) stk.pop();
      l_max[i] = (stk.empty() ? 0 : stk.top() + 1);
      stk.push(i);
    }

    stk = {};  // Clear the stack

    for (auto i = len - 1; i >= 0; --i) {
      // Pop until the stk is empty or top is less than heights[i]
      while (!stk.empty() && heights[stk.top()] >= heights[i]) stk.pop();
      r_max[i] = (stk.empty() ? len - 1 : stk.top() - 1);
      stk.push(i);
    }

    // Compute Areas of the largest rectangle for each index
    auto max_area = INT_MIN;
    for (auto i = 0; i < len; ++i) {
      auto area = (heights[i]) * (r_max[i] - l_max[i] + 1);
      max_area = max(max_area, area);
    }
    return max_area;
  }
};

TEST_CASE("84::1", "[84]") {
  const vector<int> heights = {2, 1, 5, 6, 2, 3};
  const auto expected = 10;
  REQUIRE(Solution::largestRectangleArea(heights) == expected);
}

TEST_CASE("84::2", "[84]") {
  const vector<int> heights = {2, 4};
  const auto expected = 4;
  REQUIRE(Solution::largestRectangleArea(heights) == expected);
}
