// 377_combination_sum_iv
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;
int combinationSum4(const vector<int> &A, int W) {
    vector<uint64_t> dp(W + 1);
    dp[0] = 1;
    for (auto w = 1; w <= W; w++) {
        for (auto n : A)
            if (w - n >= 0) dp[w] += dp[w - n];
    }
    return static_cast<int>(dp.back());
}

TEST_CASE("377ex1", "[377]") {
    vector<int> nums = {1, 2, 3};
    auto target = 4;
    auto expected = 7;
    REQUIRE(combinationSum4(nums, target) == expected);
}