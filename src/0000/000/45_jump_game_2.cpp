//
// Created by Nevin Zheng on 7/17/21.
//
#include <catch2/catch.hpp>
#include <vector>
using namespace std;

int jump(const vector<int> &A) {
    auto N = A.size();
    int max = 10e5 + 7;
    vector dp(N, max);
    dp.front() = 0;
    for (auto i = 0; i < N; i++) {
        for (auto j = 1; j <= A[i]; j++) {
            if (i + j >= N) continue;
            dp[i + j] = min(dp[i + j], dp[i] + 1);
        }
    }
    return dp.back();
}

TEST_CASE("45ex1", "[45]") {
    vector<int> nums = {2, 3, 1, 1, 4};
    auto expected = 2;
    auto result = jump(nums);
    REQUIRE(expected == result);
}