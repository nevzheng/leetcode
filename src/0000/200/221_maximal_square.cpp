// 221_maximal_square
// Nevin Zheng
// 7/17/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

#include <cmath>

using namespace std;

template<typename T>
using Grid = vector<vector<T>>;

int maximalSquare(Grid<char> &A) {
    auto M = A.size();
    auto N = A[0].size();
    Grid<int> dp(M, vector(N, 0));
    auto maxSquare = 0;// Assume we have no Ones
    // Fill the DP table with 1's and Zeros
    for (auto i = 0; i < M; i++) {
        for (auto j = 0; j < N; j++) {
            A[i][j] = A[i][j] - '0';
            dp[i][j] = A[i][j];
            if (dp[i][j] == 1) maxSquare = 1;// Oh we have a 1. Guards against a matrix of all zeros
        }
    }
    for (auto i = 1; i < M; i++) {
        for (auto j = 1; j < N; j++) {
            if (A[i][j]) {
                dp[i][j] = 1 + min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]);
                maxSquare = max(maxSquare, dp[i][j]);
            }
        }
    }
    return maxSquare * maxSquare;
}


TEST_CASE("221ex1", "[221]") {
    Grid<char> input = {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
    auto expected = 4;
    REQUIRE(maximalSquare(input) == expected);
}

TEST_CASE("221ex2", "[221]") {
    Grid<char> input = {{'0', '1'}, {'1', '0'}};
    auto expected = 1;
    REQUIRE(maximalSquare(input) == expected);
}

TEST_CASE("221ex3", "[221]") {
    Grid<char> input = {{'0'}};
    auto expected = 0;
    REQUIRE(maximalSquare(input) == expected);
}


TEST_CASE("221ex4", "[221]") {
    Grid<char> input = {{'1', '1', '1', '1', '0'}, {'1', '1', '1', '1', '0'}, {'1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'0', '0', '1', '1', '1'}};
    auto expected = 16;
    REQUIRE(maximalSquare(input) == expected);
}