// 454_4sum_2
// Nevin Zheng
// 8/13/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * A naive approach would be to use a quadruple for loop in O(N^4) time
 * but we can improve upon this by breaking combining the arrays into two arrays
 * this will take O(N^2) time
 * We'll use an map to count the number of times a pair sum occurs in A x B
 * We then use a approach similar to two sum where we loop for the complement of
 * c+d in CxD. if the complement of c+d exists in our map we increment the total
 */
class Solution {
 public:
  static int fourSumCount(const vector<int>& A, const vector<int>& B,
                          const vector<int>& C, const vector<int>& D) {
    unordered_map<int, int> sums;
    auto count = 0;
    for (auto a : A) {
      for (auto b : B) {
        ++sums[a + b];
      }
    }
    for (auto c : C) {
      for (auto d : D) {
        if (auto it = sums.find(-(c + d)); it != end(sums)) {
          count += it->second;
        }
      }
    }
    return count;
  }
};

TEST_CASE("454::1", "[454]") {
  vector<int> a{1, 2};
  vector<int> b{-2, -1};
  vector<int> c{-1, 2};
  vector<int> d{0, 2};
  const auto expected = 2;
  REQUIRE(Solution::fourSumCount(a, b, c, d) == expected);
}

TEST_CASE("454::2", "[454]") {
  vector<int> a{0};
  vector<int> b{0};
  vector<int> c{0};
  vector<int> d{0};
  const auto expected = 1;
  REQUIRE(Solution::fourSumCount(a, b, c, d) == expected);
}