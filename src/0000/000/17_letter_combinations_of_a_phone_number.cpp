//
// Created by Nevin Zheng on 7/16/21.
//
#include <map>
#include <set>
#include <string>
#include <vector>

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

typedef map<char, string> Dial;

void letter_combinations(const Dial &dial, const string &prefix, const string &digits, int idx, vector<string> &ans) {
    if (idx == digits.length()) {
        ans.push_back(prefix);
        return;
    }
    for (auto c : dial.at(digits[idx])) {
        letter_combinations(dial, prefix + c, digits, idx + 1, ans);
    }
}

vector<string> letterCombinations(const string &digits) {
    if (digits.empty()) return {};
    vector<string> ans;
    static Dial dial{{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
    letter_combinations(dial, "", digits, 0, ans);
    return ans;
}

TEST_CASE("17ex1", "[17]") {
    auto digits = "23";
    set<string> expected = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    auto result = letterCombinations(digits);
    set<string> result_set(begin(result), end(result));
    REQUIRE(result_set == expected);
}

TEST_CASE("17ex2", "[17]") {
    auto digits = "";
    set<string> expected = {};
    auto result = letterCombinations(digits);
    set<string> result_set(begin(result), end(result));
    REQUIRE(result_set == expected);
}

TEST_CASE("17ex3", "[17]") {
    auto digits = "2";
    set<string> expected = {"a", "b", "c"};
    auto result = letterCombinations(digits);
    set<string> result_set(begin(result), end(result));
    REQUIRE(result_set == expected);
}