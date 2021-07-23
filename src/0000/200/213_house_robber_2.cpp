// 213_house_robber_2.cpp
// Nevin Zheng
// 7/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * This problem is exactly like house robber 1, but we have an additional
 * restriction that we can't rob both the first and second houses.
 * We can apply the house robber 1 solution on [0, n-2]  and [1,n-1]
 * then take the max of the two answers
 * @param A
 * @return
 */
int rob(const vector<int>& A) {
  auto n = A.size();
  if (n == 0) return 0;
  if (n == 1) return A.front();
  vector dp1(n, INT_MIN);
  vector dp2(n, INT_MIN);
  dp1[0] = A[0];
  dp1[1] = max(A[0], A[1]);
  dp2[0] = 0;
  dp2[1] = A[1];
  for (auto i = 2UL; i < n; i++) {
    dp2[i] = max(dp2[i - 1], dp2[i - 2] + A[i]);
    if (i == n - 1) continue;  // Skip dp1 update for n-1
    dp1[i] = max(dp1[i - 1], dp1[i - 2] + A[i]);
  }
  return max(dp1[n - 2], dp2[n - 1]);
}

TEST_CASE("213ex1", "[213]") {
  const vector<int> input{2, 3, 2};
  const int expected{3};
  REQUIRE(rob(input) == expected);
}

TEST_CASE("213ex2", "[213]") {
  const vector<int> input{1, 2, 3, 1};
  const int expected{4};
  REQUIRE(rob(input) == expected);
}

TEST_CASE("213ex3", "[213]") {
  const vector<int> input{0};
  const int expected{0};
  REQUIRE(rob(input) == expected);
}

TEST_CASE("213ex4", "[213]") {
  const vector<int> input{1, 2, 1, 1};
  const int expected{3};
  REQUIRE(rob(input) == expected);
}

TEST_CASE("213ex5", "[213]") {
  const vector<int> input{1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
  const int expected{16};
  REQUIRE(rob(input) == expected);
}