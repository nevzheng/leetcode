// 90
// Nevin Zheng
// 8/3/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * In This approach we note that the powerset can be represented by
 * the integers from the range 0 to 2^(len-1) where len = the number of
 * elements of the set. If we write an integer in the range in binary
 * we can tell whether or not to include a particular element in the set
 * The algorithm is to generate all integers from 0 to 2^n
 * for each integer we'll write a loop to include elements based on
 * whether or not a particular bit is set.
 * We'll use a set and sorting to a canonical order to eliminate duplicates
 * O(2^n) time and O(n * 2^n) space
 */
// class Solution {
//  public:
//   static vector<vector<int>> subsetsWithDup(const vector<int>& nums) {
//     auto len = nums.size();
//     auto max = (1UL << len);  // 2^len -1 = max representable
//     set<vector<int>> ans;
//     for (auto cur_set = 0UL; cur_set < max; cur_set++) {
//       vector<int> v;
//       v.reserve(len);
//       for (auto j = 0UL, mask = 1UL; j < len; ++j, mask <<= 1) {
//         if (cur_set & mask) v.push_back(nums[j]);
//       }
//       std::sort(v.begin(), v.end());  // Ensure cur is in canonical order
//       ans.insert(v);
//     }
//     return vector(ans.begin(), ans.end());
//   }
// };

/**
 * This approach is based on backtracking. At Each index we can choose
 * to either include or exclude the index. when we get to the last index
 * we can copy, sort and insert into the set.
 * Using and maintaining a common prefix vector can be more memory efficient
 */
class Solution {
 public:
  set<vector<int>> subsets_;

  void dfs(const vector<int>& nums, vector<int>& prefix, size_t idx) {
    if (idx >= nums.size()) {
      vector cpy(prefix);
      std::sort(cpy.begin(), cpy.end());
      subsets_.insert(cpy);
      return;
    }
    dfs(nums, prefix, idx + 1);   // exclude current idx;
    prefix.push_back(nums[idx]);  // include current idx
    dfs(nums, prefix, idx + 1);
    prefix.pop_back();
  }

  vector<vector<int>> subsetsWithDup(const vector<int>& nums) {
    vector<int> prefix;
    dfs(nums, prefix, 0);
    return vector(subsets_.begin(), subsets_.end());
  }
};

TEST_CASE("90_subsets_2ex1", "[90]") {
  const vector<int> nums = {1, 2, 2};
  const vector<vector<int>> expected = {{},        {1}, {1, 2},
                                        {1, 2, 2}, {2}, {2, 2}};
  REQUIRE(Solution().subsetsWithDup(nums) == expected);
}
