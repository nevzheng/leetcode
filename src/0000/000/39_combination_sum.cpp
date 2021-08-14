// 39_combination_sum
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  using Vec2D = vector<vector<int>>;
  void combination_sum(Vec2D& ans, vector<int>& cur, const vector<int>& A,
                       int idx, int tgt) {
    if (tgt == 0) return ans.push_back(cur);
    if (tgt < 0 or idx >= A.size()) return;  // Went too far;
    cur.push_back(A[idx]);
    // Include idx, keep including until you can't
    combination_sum(ans, cur, A, idx, tgt - A[idx]);
    cur.pop_back();
    combination_sum(ans, cur, A, idx + 1, tgt);  // Exclude idx
  }

  Vec2D combinationSum(const vector<int>& A, int tgt) {
    vector<vector<int>> ans;
    vector<int> cur;
    combination_sum(ans, cur, A, 0, tgt);
    return ans;
  }
};

TEST_CASE("39ex1", "[39]") {
  vector<int> input = {2, 3, 6, 7};
  auto tgt = 7;
  vector<vector<int>> expected = {{2, 2, 3}, {7}};
  REQUIRE(Solution().combinationSum(input, tgt) == expected);
}