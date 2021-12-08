// 300_longest_increasing_subsequence.cpp
// Nevin Zheng
// 12/8/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// class Solution {
//  public:
//   static int lengthOfLIS(const vector<int>& a) {
//     auto N{size(a)};
//     // dp[i] = longest subsequence that ends at i
//     vector<int> dp(N, 1);
//     for (auto i = 0UL; i < N;
//          ++i) {  // grow answer, adding each additional a[i]
//       for (auto j = 0UL; j < i; ++j) {  // for j < i
//         if (a[j] < a[i]) {              // can improve answer
//           dp[i] = std::max(dp[i], dp[j] + 1);
//         }
//       }
//     }
//     return *std::max_element(begin(dp), end(dp));
//   }
// };

class Solution {
 public:
  static int lengthOfLIS(const vector<int>& a) {
    constexpr int kInf = 1e9;
    int N = size(a);
    std::vector<int> dp(N + 1, kInf);
    dp.front() = -kInf;

    for (auto i = 0; i < N; ++i) {  // Evaluate prefix arrays in sequence
      // Find the longest sequence a[i] can extend
      auto j = std::upper_bound(dp.begin(), dp.end(), a[i]) - std::begin(dp);
      // ensure extended and take min of dp[j]
      if (dp[j - 1] < a[i] && a[i] < dp[j]) {
        dp[j] = a[i];
      }
    }

    auto ans = 0;
    for (auto i = 0; i <= N; ++i) {
      if (dp[i] < kInf) {
        ans = i;
      }
    }
    return ans;
  }
};

TEST_CASE("300::1", "[300]") {
  const vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
  const auto expected = 4;
  REQUIRE(Solution::lengthOfLIS(nums) == expected);
}

TEST_CASE("300::2", "[300]") {
  const vector<int> nums{0, 1, 0, 3, 2, 3};
  const auto expected = 4;
  REQUIRE(Solution::lengthOfLIS(nums) == expected);
}

TEST_CASE("300::3", "[300]") {
  const vector<int> nums{7, 7, 7, 7, 7, 7, 7};
  const auto expected = 1;
  REQUIRE(Solution::lengthOfLIS(nums) == expected);
}