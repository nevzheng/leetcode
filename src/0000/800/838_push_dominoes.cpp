// 838_push_dominoes
// Nevin Zheng
// 7/21/21

#define CATCH_CONFIG_MAIN

#include <bits/stdc++.h>

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

string pushDominoes(const string &dominoes) {
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