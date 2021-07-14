//
// Created by Nevin Zheng on 7/14/21.
//
#include <catch2/catch.hpp>

using namespace std;

void generate_paren(vector<string> &result, const string &curr, int l, int r) {
//    cout << curr << ' ' << l << ' ' << r << '\n';
    if (l == 0 and r == 0) {// Base Case Append to the String
        result.push_back(curr);
        return;
    }
    // Place a left paren and recurse
    if (l > 0) generate_paren(result, curr + '(', l - 1, r);
    // If there are fewer left parens, we can place a right paren and recurse
    if (r > 0 && l < r) generate_paren(result, curr + ')', l, r - 1);
}

vector<string> generateParenthesis(int n) {
    int l(n), r(n);// Create Left and Right Parentheses;
    vector<string> result;
    generate_paren(result, "", l, r);
    return result;
}


TEST_CASE("22_example1") {
    auto input = 3;
    auto result = generateParenthesis(input);
    vector<string> correct = {"((()))", "(()())", "(())()", "()(())", "()()()"};
    REQUIRE(result == correct);
}
TEST_CASE("22_example2") {
    auto input = 1;
    auto result = generateParenthesis(input);
    vector<string> correct = {"()"};
    REQUIRE(result == correct);
}
