// 39_combination_sum
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  void dfs(const vector<int>& A, vector<int>& cur, int tgt, int idx,
           vector<vector<int>>& ans) {
    if (tgt == 0) return ans.push_back(cur);
    for (auto nxt = idx; nxt < static_cast<int>(A.size()); ++nxt) {
      if (nxt != idx && A[nxt] == A[nxt - 1]) continue;
      if (tgt - A[nxt] < 0) break;
      cur.push_back(A[nxt]);
      dfs(A, cur, tgt - A[nxt], nxt + 1, ans);
      cur.pop_back();
    }
  }

  vector<vector<int>> combinationSum2(vector<int>& A, int tgt) {
    vector<vector<int>> ans;
    vector<int> cur;
    std::sort(A.begin(), A.end());
    dfs(A, cur, tgt, 0, ans);
    return ans;
  }
};

TEST_CASE("40ex1", "[40]") {
  vector<int> input = {10, 1, 2, 7, 6, 1, 5};
  auto tgt = 8;
  vector<vector<int>> expected = {{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}};
  REQUIRE(Solution().combinationSum2(input, tgt) == expected);
}

TEST_CASE("40ex2", "[40]") {
  vector<int> input = {2, 5, 2, 1, 2};
  auto tgt = 5;
  vector<vector<int>> expected = {{1, 2, 2}, {5}};
  REQUIRE(Solution().combinationSum2(input, tgt) == expected);
}

TEST_CASE("40ex3", "[40]") {
  vector<int> input = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  auto tgt = 27;
  vector<vector<int>> expected = {};
  REQUIRE(Solution().combinationSum2(input, tgt) == expected);
}

TEST_CASE("40ex4", "[40]") {
  vector<int> input = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  auto tgt = 30;
  vector<vector<int>> expected = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  REQUIRE(Solution().combinationSum2(input, tgt) == expected);
}

TEST_CASE("40ex5", "[40]") {
  vector<int> input = {1, 2};
  auto tgt = 4;
  vector<vector<int>> expected = {};
  REQUIRE(Solution().combinationSum2(input, tgt) == expected);
}