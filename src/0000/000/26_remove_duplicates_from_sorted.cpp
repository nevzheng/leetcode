// 26_remove_duplicates_from_sorted
// Nevin Zheng
// 9/6/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int removeDuplicates(vector<int>& A) {
    if (A.empty()) return 0;
    auto i = 0;
    for (auto j = 0UL; j < A.size(); ++j) {
      if (A[i] != A[j]) A[++i] = A[j];
    }
    return ++i;
  }
};

TEST_CASE("26::1", "[26]") {
  vector<int> nums{1, 1, 2};
  vector<int> expected = {1, 2, 2};
  auto expected_idx = 2;
  auto idx = Solution::removeDuplicates(nums);
  REQUIRE(idx == expected_idx);
  REQUIRE(nums == expected);
}