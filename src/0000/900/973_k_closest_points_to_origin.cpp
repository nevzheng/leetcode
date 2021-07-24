// 973_k_closest_points_to_origin
// Nevin Zheng
// 7/23/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
  nth_element(begin(points), begin(points) + k, end(points),
              [](const auto& a, const auto& b) {
                return (a[0] * a[0] + a[1] * a[1]) <
                       (b[0] * b[0] + b[1] * b[1]);
              });
  return vector(begin(points), begin(points) + k);
}

TEST_CASE("973ex1", "[973]") {
  vector<vector<int>> points = {{1, 3}, {-2, 2}};
  const auto k = 1;
  const vector<vector<int>> expected = {{-2, 2}};
  auto result = kClosest(points, k);
  REQUIRE(result == expected);
}

TEST_CASE("973ex2", "[973]") {
  vector<vector<int>> points = {{3, 3}, {5, -1}, {-2, 4}};
  const auto k = 2;
  const vector<vector<int>> expected1 = {{3, 3}, {-2, 4}};
  const vector<vector<int>> expected2 = {{-2, 4}, {3, 3}};
  auto result = kClosest(points, k);
  REQUIRE((result == expected1 or result == expected2));
}