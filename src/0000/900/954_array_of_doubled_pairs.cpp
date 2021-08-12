// 954_array_of_doubled_pairs
// Nevin Zheng
// 8/11/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static bool canReorderDoubled(vector<int> arr) {
    // Push all values into a Counter
    // O(N), time + space
    unordered_map<int, int> counts;
    for (auto x : arr) ++counts[x];

    // sort by absolute value, makes sure lower magnitude gets processed first
    // O(n lg n) O(1)
    std::sort(arr.begin(), arr.end(), [](const auto a, const auto b) {
      if (abs(a) != abs(b)) return abs(a) < abs(b);
      return a < b;  // Put Negatives First
    });

    // O(N) time, O(1) space
    // Iterate over all the values, decrementing counts of x, 2*x
    for (auto x : arr) {
      if (counts[x] > 0 and counts[2 * x] > 0) {
        --counts[x];
        --counts[2 * x];
      } else if (counts[x] > 0 and counts[2 * x] == 0) {
        return false;  // Conflict Detected, not possible
      }
    }
    return true;  // True, We removed all values without conflict
  }
};

TEST_CASE("954::1", "[954]") {
  const vector<int> arr{3, 1, 3, 6};
  const bool expected = false;
  REQUIRE(Solution::canReorderDoubled(arr) == expected);
}

TEST_CASE("954::2", "[954]") {
  const vector<int> arr{2, 1, 2, 6};
  const bool expected = false;
  REQUIRE(Solution::canReorderDoubled(arr) == expected);
}

TEST_CASE("954::3", "[954]") {
  const vector<int> arr{1, 2, 4, 16, 8, 4};
  const bool expected = false;
  REQUIRE(Solution::canReorderDoubled(arr) == expected);
}

TEST_CASE("954::4", "[954]") {
  const vector<int> arr{4, -2, 2, -4};
  const bool expected = true;
  REQUIRE(Solution::canReorderDoubled(arr) == expected);
}
