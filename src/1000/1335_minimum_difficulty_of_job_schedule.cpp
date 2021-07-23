// 1335_minimum_difficulty_of_job_schedule
// Nevin Zheng
// 7/22/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

int minDifficulty(const vector<int>& A, int n_days) {
  auto n_jobs = static_cast<int>(A.size());
  if (n_days > n_jobs) return -1;  // More Days than tasks
  vector dp(n_days, vector(n_jobs, INT_MAX));
  // For 1 day, 0th index, dp[0][i] is max value up to and including i;
  inclusive_scan(begin(A), end(A), begin(dp[0]),
                 [](auto a, auto b) { return max(a, b); });
  for (auto d = 1; d < n_days; d++) {
    for (auto n = d; n < n_jobs; n++) {
      auto mx = 0;
      auto mn = INT_MAX;
      for (auto k = n; k >= d; k--) {
        mx = max(mx, A[k]);
        mn = min(mn, dp[d - 1][k - 1] + mx);
      }
      dp[d][n] = mn;
    }
  }
  return dp.back().back();
}

TEST_CASE("1335ex1", "[1335]") {
  const vector jd{6, 5, 4, 3, 2, 1};
  const auto d = 2;
  const auto expected = 7;
  REQUIRE(minDifficulty(jd, d) == expected);
}

TEST_CASE("1335ex2", "[1335]") {
  const vector jd{9, 9, 9};
  const auto d = 4;
  const auto expected = -1;
  REQUIRE(minDifficulty(jd, d) == expected);
}

TEST_CASE("1335ex3", "[1335]") {
  const vector jd{1, 1, 1};
  const auto d = 3;
  const auto expected = 3;
  REQUIRE(minDifficulty(jd, d) == expected);
}

TEST_CASE("1335ex4", "[1335]") {
  const vector jd{7, 1, 7, 1, 7, 1};
  const auto d = 3;
  const auto expected = 15;
  REQUIRE(minDifficulty(jd, d) == expected);
}
