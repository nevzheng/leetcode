// 1235_maximum_profit_in_job_scheduling
// Nevin Zheng
// 8/28/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * We will use dynamic programming to gradually build an optimal answer
 * We will first construct jobs as a tuple of (end, start, val)
 * then create an array of all jobs
 * We then lexicographically sort the array.
 * We construct our DP as a map<int,int> such that dp[end] = maxProfit
 * means that the the maxProfit up to end is maxProfit
 * we then iterate over our lexicographically sorted list of jobs
 * we search for the insertion point of the job
 * in the list with prev(upperbound(start)).
 * If including the job improves the result, we will insert it.
 * At the end of the loop, we return the profit of the last element in the map
 */
class Solution {
 public:
  // End, Start, Val
  using Job = tuple<int, int, int>;
  static int jobScheduling(const vector<int>& startTime,
                           const vector<int>& endTime,
                           const vector<int>& profit) {
    auto len = startTime.size();
    vector<Job> jobs;
    jobs.reserve(len);
    for (auto i = 0UL; i < len; ++i)
      jobs.emplace_back(endTime[i], startTime[i], profit[i]);
    std::sort(jobs.begin(), jobs.end());
    // maxProfit at 0 is 0
    std::map<int, int> dp{{0, 0}};
    for (const auto& [end, start, val] : jobs) {
      // Find Last Possible Insertion Point of Job
      // find its value, then add value of current job
      auto cur = std::prev(dp.upper_bound(start))->second + val;
      // Insert into DP if answer improves
      // Final/Last Value only overwritten if end is greater
      if (cur > dp.rbegin()->second) dp[end] = cur;
    }
    return dp.rbegin()->second;
  }
};

TEST_CASE("1235::1", "[1235]") {
  const vector<int> start_time{1, 2, 3, 3};
  const vector<int> end_time{3, 4, 5, 6};
  const vector<int> profit{50, 10, 40, 70};
  const auto expected = 120;
  REQUIRE(Solution::jobScheduling(start_time, end_time, profit) == expected);
}

TEST_CASE("1235::2", "[1235]") {
  const vector<int> start_time{1, 2, 3, 4, 6};
  const vector<int> end_time{3, 5, 10, 6, 9};
  const vector<int> profit{20, 20, 100, 70, 60};
  const auto expected = 150;
  REQUIRE(Solution::jobScheduling(start_time, end_time, profit) == expected);
}