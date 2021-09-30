// 698_partition_to_k_equal_sum_subsets
// Nevin Zheng
// 9/30/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  bool canPartition(vector<int>& nums, vector<bool>& visited, size_t start,
                    int k, int curSum, size_t idx, int tgt) {
    if (k == 0) return true;         // found all subsets indexed 0...n-1
    if (curSum == tgt && idx > 0) {  // Found, move to nxt subset
      return canPartition(nums, visited, 0, k - 1, 0, 0, tgt);
    }
    for (auto i = start; i < nums.size(); ++i) {  // Explore all nodes
      if (!visited[i]) {                          // Use if available
        visited[i] = true;                        // Mark i as used
        // Successful call, return
        if (canPartition(nums, visited, i + 1, k, curSum + nums[i], idx++, tgt))
          return true;
        visited[i] = false;  // free index for other searches
      }
    }
    return false;
  }
  bool canPartitionKSubsets(vector<int>& nums, int k) {
    auto sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (k == 0 || sum % k != 0) return false;
    vector<bool> visited(nums.size());
    return canPartition(nums, visited, 0, k - 1, 0, 0, sum / k);
  }
};
