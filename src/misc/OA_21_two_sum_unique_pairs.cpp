// OA_21_two_sum_unique_pairs
// Nevin Zheng
// 8/11/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We'll apply a sorted two sum solution.
 * We sort the numbers in O(nlgn) time
 * We then use two pointers to find pairs taht sum to target.
 * This will take O(n) time and O(n) space, depending on the number of pairs
 * Our strategy to eliminate duplicates can be to use a set. if it's unordered
 * then eliminating duplicates will not affect our complexity
 * If sets are disallowed we can use the remove uniques stl idiom to eliminate
 * duplicates. This can be done in linear time
 * After duplicates are eliminated. We can return the size of the set
 * O(nlgn) time, O(n) space for result, O(1) for computation
 */
class Solution {
 public:
  static int countPairs(vector<int>& A, int tgt) {
    std::sort(A.begin(), A.end());  // n lgn
    vector<pair<int, int>> pairs;
    auto l = 0UL;
    auto r = A.size() - 1;
    while (l < r) {
      auto sum = A[l] + A[r];
      if (sum <= tgt) {
        if (sum == tgt) pairs.emplace_back(A[l], A[r]);
        ++l;  // keep searching
      } else {
        --r;  // shrink sum
      }
    }
    return static_cast<int>(
        distance(pairs.begin(), std::unique(pairs.begin(), pairs.end())));
  }
};

TEST_CASE("OA::21::1", "[oa21]") {
  const vector<int> a{1, 1, 2, 45, 46, 46};
  const auto target = 47;
  const auto expected = 2;
  REQUIRE(Solution::countPairs(a, target) == expected);
}

TEST_CASE("OA::21::2", "[oa21]") {
  const vector<int> a{1, 1};
  const auto target = 2;
  const auto expected = 1;
  REQUIRE(Solution::countPairs(a, target) == expected);
}

TEST_CASE("OA::21::3", "[oa21]") {
  const vector<int> a{1, 5, 1, 5};
  const auto target = 6;
  const auto expected = 1;
  REQUIRE(Solution::countPairs(a, target) == expected);
}
