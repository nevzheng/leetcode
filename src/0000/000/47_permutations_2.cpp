// 47_permutations_2
// Nevin Zheng
// 8/14/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  void permute_unique(vector<int>& A, size_t idx, vector<vector<int>>& ans) {
    if (idx == A.size()) return ans.push_back(A);
    set<int> s;  // Skip Calls for duplicate Values
    for (auto i = idx; i < A.size(); ++i) {
      if (s.count(A[i])) continue;
      s.insert(A[i]);
      std::swap(A[idx], A[i]);
      permute_unique(A, idx + 1, ans);
      std::swap(A[idx], A[i]);
    }
  }

  vector<vector<int>> permuteUnique(vector<int>& A) {
    vector<vector<int>> ans;
    std::sort(A.begin(), A.end());  // Ensure nums are in order;
    permute_unique(A, 0, ans);
    return ans;
  }
};

TEST_CASE("47::1", "{46}") {
  vector<int> nums{1, 1, 2};
  auto result = Solution().permuteUnique(nums);
  std::sort(result.begin(), result.end());
  vector<vector<int>> expected{{1, 1, 2}, {1, 2, 1}, {2, 1, 1}};
  REQUIRE(result == expected);
}

TEST_CASE("47::2", "{46}") {
  vector<int> nums{1, 2, 3};
  auto result = Solution().permuteUnique(nums);
  std::sort(result.begin(), result.end());
  vector<vector<int>> expected{{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                               {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
  REQUIRE(result == expected);
}

TEST_CASE("47::3", "{46}") {
  vector<int> nums{2, 2, 1, 1};
  auto result = Solution().permuteUnique(nums);
  std::sort(result.begin(), result.end());
  vector<vector<int>> expected{{1, 1, 2, 2}, {1, 2, 1, 2}, {1, 2, 2, 1},
                               {2, 1, 1, 2}, {2, 1, 2, 1}, {2, 2, 1, 1}};
  REQUIRE(result == expected);
}