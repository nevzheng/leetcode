// OA_30_optimal_utilization
// Nevin Zheng
// 8/12/21

// https://leetcode.com/discuss/interview-question/373202
// https://github.com/Zhouzhiling/leetcode/blob/master/Amazon.Optimal%20Utilization.md

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * In this solution we will test all possible pairs
 * This can be done in O(MN) time and space
 */
class SolutionBruteForce {
 public:
  static vector<vector<int>> optimalUtilization(const vector<vector<int>>& a,
                                                const vector<vector<int>>& b,
                                                int tgt) {
    int best = INT_MIN;
    vector<vector<int>> ans;
    for (const auto& x : a) {
      for (const auto& y : b) {
        if (x.front() == y.front()) continue;  // Ignore Same Id
        auto sum = x.back() + y.back();
        if (sum > tgt) continue;  // Ignore larger
        // Extend Current Answer
        if (sum == best) ans.push_back({x.front(), y.front()});
        if (best < sum and sum <= tgt) {  // Replace Current Answer
          best = sum;
          ans.clear();
          ans.push_back({x.front(), y.front()});
        }
      }
    }
    return ans;
  }
};

/**
 * This implementation improves upon the brute force version by
 * applying sorting the vectors and applying binary search to find
 * the best match for each candidate.
 * Key Trick is to use upper bound and std::prev
 *
 */
class Solution {
 public:
  static vector<vector<int>> optimalUtilization(vector<vector<int>>& a,
                                                vector<vector<int>>& b,
                                                int tgt) {
    // Given m=len(a) and n=len(b), Bruteforce takes O(MN) time/space
    // We perform binary search on one of the arrays IE M*lg(N) or lg(M) * N
    // it's more efficient if the longer array is binary searched,
    // Thus a should be shorter
    // We can flip the arrays and apply a fixup procedure to fix the indices
    if (a.size() > b.size()) {
      auto tmp = optimalUtilization(b, a, tgt);       // Ensure a is shorter
      for (auto& v : tmp) swap(v.front(), v.back());  // Flip Indices
      return tmp;
    }

    int best = INT_MIN;
    vector<vector<int>> ans;
    auto cmp = [](const auto& x, const auto& y) { return x.back() < y.back(); };
    std::sort(a.begin(), a.end(), cmp);
    std::sort(b.begin(), b.end(), cmp);
    for (const auto& x : a) {
      auto p = vector{std::numeric_limits<int>::min(), tgt - x.back()};
      auto yt = std::upper_bound(b.cbegin(), b.cend(), p, cmp);
      if (yt == b.begin()) continue;  // No valid pair
      yt = std::prev(yt);             // Get the Last element LEQ to tgt
      if (x.front() == yt->front()) continue;  // Ignore Same ID
      auto sum = x.back() + yt->back();
      if (sum == best) ans.push_back({x.front(), yt->front()});
      if (best < sum and sum <= tgt) {
        best = sum;
        ans.clear();
        ans.push_back({x.front(), yt->front()});
      }
    }
    return ans;
  }
};

TEST_CASE("OA::30::1", "[oa30]") {
  vector<vector<int>> a{{1, 2}, {2, 4}, {3, 6}};  // NOLINT
  vector<vector<int>> b{{1, 2}};
  const auto tgt = 7;
  const vector<vector<int>> expected{{2, 1}};
  REQUIRE(Solution::optimalUtilization(a, b, tgt) == expected);
}

TEST_CASE("OA::30::2", "[oa30]") {
  vector<vector<int>> a{{1, 3}, {2, 5}, {3, 7}, {4, 10}};  // NOLINT
  vector<vector<int>> b{{1, 2}, {2, 3}, {3, 4}, {4, 5}};   // NOLINT
  const auto tgt = 10;
  const vector<vector<int>> expected{{2, 4}, {3, 2}};
  REQUIRE(Solution::optimalUtilization(a, b, tgt) == expected);
}

TEST_CASE("OA::30::3", "[oa30]") {
  vector<vector<int>> a{{1, 8}, {2, 7}, {3, 14}};   // NOLINT
  vector<vector<int>> b{{1, 5}, {2, 10}, {3, 14}};  // NOLINT
  const auto tgt = 20;
  const vector<vector<int>> expected{{3, 1}};
  REQUIRE(Solution::optimalUtilization(a, b, tgt) == expected);
}

TEST_CASE("OA::30::4", "[oa30]") {
  vector<vector<int>> a{{1, 8}, {2, 15}, {3, 9}};   // NOLINT
  vector<vector<int>> b{{1, 8}, {2, 11}, {3, 12}};  // NOLINT
  const auto tgt = 20;
  const vector<vector<int>> expected{{1, 3}, {3, 2}};
  REQUIRE(Solution::optimalUtilization(a, b, tgt) == expected);
}
