// 322_coin_change
// Nevin Zheng
// 7/20/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

int coinChange(const vector<int> &A, int W) {
    vector<int> dp(W + 1, 1e5 + 7);// Number of Coins needed to make W
    dp[0] = 0;                     // 0 coins to make val of 0
    for (auto w = 1; w <= W; w++) {
        for (auto x : A) {
            if (w - x < 0) continue;// Skip values that are out of range
            dp[w] = min(dp[w], 1 + dp[w - x]);
        }
    }
    return dp.back() != 1e5 + 7 ? dp.back() : -1;
}