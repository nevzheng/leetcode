// 85
// Nevin Zheng
// 8/21/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * Please review 84_largest_rectangle_in_histogram
 * We can solve that in O(n) time and space
 *
 * We can use 84 to solve 85. In short we can imagine
 * creating a histogram from the first row
 * computing the largest rectangle and updating it with each additional row
 * and then computing the largest rectanble again.
 * the update rule is if there is a zero then row[i] =0 otherwise increment
 *
 * Given an MxN matrix. We can solve a row in O(N) time and space
 * Thus we can solve in O(MN) time and O(N) space
 */
class Solution {
 public:
  // Import 84_largest_rectangle_solver
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

  static void update_row(vector<int>& cur, const vector<int>& next) {
    if (cur.empty()) {
      cur = next;
    } else {
      for (auto i = 0UL; i < cur.size(); ++i)
        cur[i] = next[i] != 0 ? cur[i] + 1 : 0;
    }
  }

  static vector<vector<int>> make_int_matrix(
      const vector<vector<char>>& matrix) {
    vector<vector<int>> mat(matrix.size(), vector<int>(matrix.front().size()));
    for (auto i = 0UL; i < matrix.size(); ++i) {
      for (auto j = 0UL; j < matrix.front().size(); ++j) {
        mat[i][j] = matrix[i][j] - '0';
      }
    }
    return mat;
  }

  static int maximalRectangle(const vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    auto max_area = INT_MIN;
    vector<int> cur;
    auto mat = make_int_matrix(matrix);
    for (const auto& row : mat) {
      update_row(cur, row);  // Add a new row
      auto area = largestRectangleArea(cur);
      max_area = max(max_area, area);  // Take a max
    }
    return max_area;
  }
};

TEST_CASE("85::1", "[85]") {
  const vector<vector<char>> matrix{{'1', '0', '1', '0', '0'},
                                    {'1', '0', '1', '1', '1'},
                                    {'1', '1', '1', '1', '1'},
                                    {'1', '0', '0', '1', '0'}};
  const auto expected = 6;
  REQUIRE(Solution::maximalRectangle(matrix) == expected);
}