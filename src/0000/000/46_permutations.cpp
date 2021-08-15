// 46_permutations
// Nevin Zheng
// 8/14/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// class Solution {
//  public:
//   vector<vector<int>> permute(vector<int>& nums) {
//     vector<vector<int>> ans;
//     std::sort(nums.begin(), nums.end());
//     do {
//       ans.push_back(nums);
//     } while (std::next_permutation(nums.begin(), nums.end()));
//     return ans;
//   }
// };

class Solution {
 public:
  void perm(vector<int>& A, size_t idx, vector<vector<int>>& ans) {
    if (idx == A.size()) return ans.push_back(A);
    for (auto i = idx; i < A.size(); ++i) {
      std::swap(A[idx], A[i]);
      perm(A, idx + 1, ans);
      std::swap(A[idx], A[i]);
    }
  }

  vector<vector<int>> permute(vector<int>& A) {
    vector<vector<int>> ans;
    perm(A, 0, ans);
    return ans;
  }
};

TEST_CASE("46::1", "{46}") {
  vector<int> nums{1, 2, 3};
  auto result = Solution().permute(nums);
  std::sort(result.begin(), result.end());
  vector<vector<int>> expected{{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                               {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
  REQUIRE(result == expected);
}

TEST_CASE("46::2", "{46}") {
  vector<int> nums{0, 1};
  auto result = Solution().permute(nums);
  vector<vector<int>> expected{{0, 1}, {1, 0}};
  REQUIRE(result == expected);
}

TEST_CASE("46::3", "{46}") {
  vector<int> nums{1};
  auto result = Solution().permute(nums);
  vector<vector<int>> expected{{1}};
  REQUIRE(result == expected);
}