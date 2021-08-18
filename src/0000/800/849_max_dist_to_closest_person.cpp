// 849_max_dist_to_closest_person
// Nevin Zheng
// 8/18/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * To Solve this problem we will search the array for the largest groups of 0s
 * For a group of size k:
 * If the group is at the front or back then the answer is k
 * if its sandwiched between 1s the answer is k+1 /2
 * We will iterate through the array tracking the best answer
 *
 * O(N) time, O(1) space
 */
class Solution {
 public:
  static int maxDistToClosest(const vector<int>& seats) {
    auto n = static_cast<int>(seats.size());
    auto mx = 0;
    auto k = 0;  // longest run of zeros
    // Look For Runs of Zeros
    for (auto i = 0; i < n; ++i) {
      if (seats[i]) {
        k = 0;
      } else {
        mx = max(mx, (++k + 1) / 2);
      }
    }

    // Group of Zeros on the Left Edge
    for (auto i = 0; i < n; ++i) {
      if (seats[i]) {
        mx = max(mx, i);
        break;
      }
    }
    // Group of Zeros on the Right Edge
    for (auto i = n - 1; i >= 0; --i) {
      if (seats[i]) {
        mx = max(mx, ((n - 1) - i));
        break;
      }
    }
    return mx;
  }
};

TEST_CASE("849::1", "[849]") {
  const vector<int> seats = {1, 0, 0, 0, 1, 0, 1};
  const int expected = 2;
  REQUIRE(Solution::maxDistToClosest(seats) == expected);
}

TEST_CASE("849::2", "[849]") {
  const vector<int> seats = {1, 0, 0, 0};
  const int expected = 3;
  REQUIRE(Solution::maxDistToClosest(seats) == expected);
}

TEST_CASE("849::3", "[849]") {
  const vector<int> seats = {0, 1};
  const int expected = 1;
  REQUIRE(Solution::maxDistToClosest(seats) == expected);
}

TEST_CASE("849::4", "[849]") {
  const vector<int> seats = {1, 0, 0, 0, 0, 1, 0, 1};
  const int expected = 2;
  REQUIRE(Solution::maxDistToClosest(seats) == expected);
}

TEST_CASE("849::5", "[849]") {
  const vector<int> seats = {1, 0, 0, 1, 0, 0, 0};
  const int expected = 3;
  REQUIRE(Solution::maxDistToClosest(seats) == expected);
}