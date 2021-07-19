// 39_combination_sum
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using Vec2D = vector<vector<int>>;
void combination_sum2(Vec2D &ans, vector<int> curr, const vector<int> &A, int idx, int tgt) {
    if (tgt == 0) {
        sort(begin(curr), end(curr));
        return ans.push_back(curr);
    };
    if (tgt < 0 or idx >= A.size()) return;      // Went too far;
    combination_sum2(ans, curr, A, idx + 1, tgt);// Exclude idx
    curr.push_back(A[idx]);
    combination_sum2(ans, curr, A, idx + 1, tgt - A[idx]);// Include idx
}

Vec2D combinationSum2(vector<int> &A, int tgt) {
    // Do a sanity check
    if (accumulate(begin(A), end(A), 0) < tgt) return {};
    // Do Some Additional Pruning;
    // If there are larger elements in the array, they'll be excluded quickly
    vector<vector<int>> ans;
    combination_sum2(ans, {}, A, 0, tgt);
    sort(begin(ans), end(ans));
    ans.erase(unique(begin(ans), end(ans)), end(ans));
    return ans;
}


TEST_CASE("40ex1", "[40]") {
    vector<int> input = {10, 1, 2, 7, 6, 1, 5};
    auto tgt = 8;
    vector<vector<int>> expected = {{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}};
    REQUIRE(combinationSum2(input, tgt) == expected);
}

TEST_CASE("40ex2", "[40]") {
    vector<int> input = {2, 5, 2, 1, 2};
    auto tgt = 5;
    vector<vector<int>> expected = {{1, 2, 2}, {5}};
    REQUIRE(combinationSum2(input, tgt) == expected);
}

TEST_CASE("40ex3", "[40]") {
    vector<int> input = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    auto tgt = 27;
    vector<vector<int>> expected = {};
    REQUIRE(combinationSum2(input, tgt) == expected);
}