// 587_erect_the_fence
// Nevin Zheng
// 9/3/21
// https://leetcode.com/problems/erect-the-fence/discuss/1442266/A-Detailed-Explanation-with-Diagrams-(Graham-Scan)

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;
class Solution {
 public:
  struct Point {
    int x;
    int y;
    explicit Point(vector<int>& tree) : x(tree[0]), y(tree[1]) {}
  };

  /**
   * Determine the Cross Product between AB and BC
   * The Sign of AB x BC indicate whether:
   *    + Collinear: 0
   *    + Clockwise < 0
   *    + CounterClockwise > 0
   * @param a
   * @param b
   * @param c
   * @return
   */
  static int crossProduct(const Point& a, const Point& b, const Point& c) {
    auto [v1x, v1y] = make_tuple(b.x - a.x, b.y - a.y);  // AB
    auto [v2x, v2y] = make_tuple(c.x - b.x, c.y - b.y);  // BC
    return (v1x * v2y) - (v2x * v1y);
  }

  static vector<Point> convexHull(vector<Point>& points) {
    std::sort(points.begin(), points.end(), [](const auto& a, const auto& b) {
      return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });  // Lex Sort all Points
    vector<Point> ans;
    // Compute Lower Hull, Left to Right
    for (const auto& p : points) {
      // Disallow Clockwise turns
      while (ans.size() > 1 &&
             (crossProduct(ans[ans.size() - 2], ans[ans.size() - 1], p) < 0)) {
        ans.pop_back();
      }
      ans.push_back(p);
    }
    // Edge Case, all points are colinear
    if (std::size(ans) == std::size(points)) return ans;
    // Compute Upper Hull, Right to Left. Avoid Duplicating last point
    for (int i = static_cast<int>(points.size()) - 2; i >= 0; --i) {
      auto p = points[i];
      while (ans.size() > 1 &&
             (crossProduct(ans[ans.size() - 2], ans[ans.size() - 1], p) < 0)) {
        ans.pop_back();
      }
      ans.push_back(p);
    }
    ans.pop_back();  // Remove Duplicate of first point
    std::sort(ans.begin(), ans.end(), [](const auto& a, const auto& b) {
      return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });  // Lex Sort all Points
    return ans;
  }

  static vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
    std::vector<Point> points(begin(trees), end(trees));
    auto result = convexHull(points);
    trees.clear();
    std::transform(result.begin(), result.end(), back_inserter(trees),
                   [](const auto& p) {
                     return vector<int>{p.x, p.y};
                   });
    return trees;
  }
};

TEST_CASE("587::1", "[587]") {
  vector<vector<int>> points{{1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {4, 2}};
  vector<vector<int>> expected{{1, 1}, {2, 0}, {3, 3}, {2, 4}, {4, 2}};
  std::sort(expected.begin(), expected.end());
  REQUIRE(Solution::outerTrees(points) == expected);
}