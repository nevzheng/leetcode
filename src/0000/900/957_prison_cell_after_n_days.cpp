// 957_prison_cell_after_n_days
// Nevin Zheng
// 8/11/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using Cells = vector<int>;
class Solution {
 public:
  static vector<int> prisonAfterNDays(const vector<int>& cells, int n) {
    vector<Cells> seen;
    Cells cur(cells);
    Cells next(cells.size());
    while (n--) {
      for (auto i = 1UL; i < cells.size() - 1; ++i) {
        next[i] = cur[i - 1] == cur[i + 1] ? 1 : 0;
      }
      if (!seen.empty() && next == seen.front()) {
        n %= static_cast<int>(seen.size());
      } else {
        seen.push_back(next);
      }
      cur = next;
    }
    return cur;
  }
};

TEST_CASE("957::1", "[957]") {
  const vector cells{0, 1, 0, 1, 1, 0, 0, 1};
  const auto n = 7;
  const vector expected{0, 0, 1, 1, 0, 0, 0, 0};
  REQUIRE(Solution::prisonAfterNDays(cells, n) == expected);
}

TEST_CASE("957::2", "[957]") {
  const vector cells{1, 0, 0, 1, 0, 0, 1, 0};
  const auto n = 1'000'000'000;
  const vector expected{0, 0, 1, 1, 1, 1, 1, 0};
  REQUIRE(Solution::prisonAfterNDays(cells, n) == expected);
}
