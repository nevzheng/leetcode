// 53_max_subarray
// Nevin Zheng
// 7/27/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

int maxSubArray(const vector<int>& nums) {
  int g_max = INT_MIN;
  int l_max = 0;
  for (auto x : nums) {
    l_max = max(x, l_max + x);
    g_max = max(g_max, l_max);
  }
  return g_max;
}

// int maxSubArray(const vector<int>& a) {
//   auto l_mx = 0;
//   auto g_mx = INT_MIN;
//   auto cur_st = 0UL;
//   auto bst_st = 0UL;
//   auto bst_en = 0UL;
//   for (auto i = 0UL; i < a.size(); i++) {
//     if (l_mx <= 0) {
//       l_mx = a[i];
//       cur_st = i;
//     } else {
//       l_mx += a[i];
//     }
//     if (l_mx > g_mx) {
//       g_mx = l_mx;
//       bst_st = cur_st;
//       bst_en = i + 1; // Make range exclusive
//     }
//   }
//   cout << bst_st << ' ' << bst_en << '\n';
//   return g_mx;
// }

TEST_CASE("53ex1", "[53]") {
  const auto input = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  const auto expected = 6;
  REQUIRE(maxSubArray(input) == expected);
}

TEST_CASE("53ex2", "[53]") {
  const auto input = {1};
  const auto expected = 1;
  REQUIRE(maxSubArray(input) == expected);
}

TEST_CASE("53ex3", "[53]") {
  const auto input = {5, 4, -1, 7, 8};
  const auto expected = 23;
  REQUIRE(maxSubArray(input) == expected);
}