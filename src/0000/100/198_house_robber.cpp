// 198_house_robber
// Nevin Zheng
// 7/22/21

#include <catch2/catch.hpp>

using namespace std;

int rob(const vector<int>& A) {
  auto n = static_cast<int>(A.size());
  if (n == 0) return -1;
  if (n == 1) return A.front();
  if (n == 2) return max(A.front(), A.back());
  vector dp(n, INT_MIN);  // dp[i] =  max gained if you rob up to the ith house
  tie(dp[0], dp[1]) = tie(A[0], max(A[0], A[1]));
  // Best answer is either skip house and carry over i-1
  // or rob house add add val from i-2
  for (auto i = 2; i < n; i++) dp[i] = max(dp[i - 1], dp[i - 2] + A[i]);
  return dp.back();
}

TEST_CASE("198ex1", "[198]") {
  const vector<int> input{1, 2, 3, 1};
  const auto expected{4};
  REQUIRE(rob(input) == expected);
}

TEST_CASE("198ex2", "[198]") {
  const vector<int> input{2, 7, 9, 3, 1};
  const auto expected{12};
  REQUIRE(rob(input) == expected);
}
