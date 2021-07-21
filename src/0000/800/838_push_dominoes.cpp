// 838_push_dominoes
// Nevin Zheng
// 7/21/21
#include <bits/stdc++.h>

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

string pushDominoes(const string &dominoes) {
    auto N = dominoes.size();
    if (N == 1) return dominoes;// Singular Case
    string state(dominoes), next_state;
    auto updateCount = INT_MAX;
    while (updateCount) {
        updateCount = 0;
        next_state = state;
        //         Handle the First and Last Dominoes
        if (state[0] == '.' and state[1] == 'L') {
            next_state[0] = 'L';
            updateCount++;
        }
        if (state[N - 1] == '.' and state[N - 2] == 'R') {
            next_state[N - 1] = 'R';
            updateCount++;
        }
        for (auto i = 1ul; i <= state.size() - 2; i++) {
            if (state[i] == '.') {
                if ((state[i - 1] == 'R' and state[i + 1] == 'L') or// Equal Force on Vertical)
                    (state[i - 1] == '.' and state[i + 1] == '.') or// Surrounded by Verticals
                    (state[i - 1] == 'L' and state[i + 1] == 'R')   // Force Not Applied to Domino
                ) {
                    continue;
                } else if (state[i - 1] == 'R') {//Domino Will Fall to the right.
                    next_state[i] = 'R';
                    updateCount++;
                } else if (state[i + 1] == 'L') {// Domino will fall to the left
                    next_state[i] = 'L';
                    updateCount++;
                }
            }
        }
        state = next_state;// Update the state
    }
    return state;
}

TEST_CASE("838ex1", "[838]") {
    auto input = "RR.L";
    auto expected = "RR.L";
    REQUIRE(pushDominoes(input) == expected);
}

TEST_CASE("838ex2", "[838]") {
    auto input = ".L.R...LR..L..";
    auto expected = "LL.RR.LLRRLL..";
    REQUIRE(pushDominoes(input) == expected);
}

TEST_CASE("838ex3", "[838]") {
    auto input = "L";
    auto expected = "L";
    REQUIRE(pushDominoes(input) == expected);
}

TEST_CASE("838ex4", "[838]") {
    auto input = "R.";
    auto expected = "RR";
    REQUIRE(pushDominoes(input) == expected);
}

TEST_CASE("838ex5", "[838]") {
    auto input = ".L";
    auto expected = "LL";
    REQUIRE(pushDominoes(input) == expected);
}

TEST_CASE("838ex6", "[838]") {
    auto input = "..R..";
    auto expected = "..RRR";
    REQUIRE(pushDominoes(input) == expected);
}
