// 303_range_sum_query_immutable
// Nevin Zheng
// 8/16/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class NumArray {
 public:
  vector<int> nums_;
  vector<int> prefix_;
  NumArray(vector<int>& nums) : nums_(nums) {
    std::partial_sum(nums.begin(), nums.end(), back_inserter(prefix_));
  }

  int sumRange(int left, int right) {
    return prefix_[right] - prefix_[left] + nums_[left];
  }
};
