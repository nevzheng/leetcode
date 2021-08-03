// 50_power
// Nevin Zheng
// 8/3/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static double myPow(double x, int n) {
    if (n == 0) return 1.;
    double ans = 1.;
    auto nn = n > 0 ? n : -static_cast<long>(n);
    while (nn > 0) {
      if (nn % 2 == 0) {
        x *= x;
        nn /= 2;
      } else {
        ans = ans * x;
        --nn;
      }
    }
    return n > 0 ? ans : 1. / ans;
  }
};

TEST_CASE("50ex1", "[50]") {
  const auto x = 2.;
  const auto n = 10;
  const auto expected = 1024.;
  REQUIRE(Solution::myPow(x, n) - expected <= .005);
}

TEST_CASE("50ex2", "[50]") {
  const auto x = 2.1;
  const auto n = 3;
  const auto expected = 9.261;
  REQUIRE(Solution::myPow(x, n) - expected <= .005);
}

TEST_CASE("50ex3", "[50]") {
  const auto x = 2.;
  const auto n = -2.;
  const auto expected = .25;
  REQUIRE(Solution::myPow(x, n) - expected <= .005);
}