// 416_partition_equal_subset_sum
// Nevin Zheng
// 7/17/21


#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * This Implementation of knapsack is O(N*tgt)
 * @param A
 * @param N
 * @param tgt
 * @return
 */
bool knapsack(const vector<int> &A, int N, int tgt) {
    // dp[n][w] Is it possible to make reach exactly weight w with 0..i items?
    vector<vector<bool>> dp(N + 1, vector(tgt + 1, false));
    for (auto i = 0; i <= N; i++) dp[i][0] = true;   // It's possible to reach [i][0], bascially EXCLUDE
    for (auto i = 1; i <= tgt; i++) dp[0][i] = false;// Not possible to reach any value with 0 items

    for (auto i = 1; i <= N; i++) {
        for (auto w = 1; w <= tgt; w++) {
            auto wt = A[i - 1];
            if (wt <= w) dp[i][w] = dp[i - 1][w - wt] or dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[N][tgt];
}

bool canPartition(const vector<int> &A) {
    int N = A.size();
    int sum = accumulate(begin(A), end(A), 0);// O(N), O(1)
    if (sum % 2) return false;
    return knapsack(A, N, sum / 2);// O(N^2), O(N)
}


TEST_CASE("416Example1", "[416]") {
    auto input = {1, 5, 11, 5};
    auto expected = true;
    REQUIRE(canPartition(input) == expected);
}


TEST_CASE("416Example2", "[416]") {
    auto input = {1, 2, 3, 5};
    auto expected = false;
    REQUIRE(canPartition(input) == expected);
}

TEST_CASE("416Example3", "[416]") {
    auto input = {2, 2, 1, 1};
    auto expected = true;
    REQUIRE(canPartition(input) == expected);
}

TEST_CASE("416Example4", "[416]") {
    auto input = {1, 2, 5};
    auto expected = false;
    REQUIRE(canPartition(input) == expected);
}