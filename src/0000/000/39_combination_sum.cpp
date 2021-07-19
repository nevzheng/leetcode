// 39_combination_sum
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using Vec2D = vector<vector<int>>;
void combination_sum(Vec2D &ans, const vector<int> &curr, const vector<int> &A, int idx, int tgt) {
    if (tgt == 0) return ans.push_back(curr);
    if (tgt < 0 or idx >= A.size()) return;// Went too far;
    vector<int> inc(curr);
    inc.push_back(A[idx]);
    combination_sum(ans, inc, A, idx, tgt - A[idx]);// Include idx, keep including until you can't
    combination_sum(ans, curr, A, idx + 1, tgt);    // Exclude idx
}

Vec2D combinationSum(const vector<int> &A, int tgt) {
    vector<vector<int>> ans;
    combination_sum(ans, {}, A, 0, tgt);
    return ans;
}


TEST_CASE("39ex1", "[39]") {
    vector<int> input = {2, 3, 6, 7};
    auto tgt = 7;
    vector<vector<int>> expected = {{2, 2, 3}, {7}};
    REQUIRE(combinationSum(input, tgt) == expected);
}