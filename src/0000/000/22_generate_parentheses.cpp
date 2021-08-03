//
// Created by Nevin Zheng on 7/14/21.
//
#include <catch2/catch.hpp>

using namespace std;

void generate_paren(vector<string>& result, string& cur, int l, int r) {
  //    cout << curr << ' ' << l << ' ' << r << '\n';
  if (l == 0 and r == 0) {  // Base Case Append to the String
    result.push_back(cur);
    return;
  }
  // Place a left paren and recurse
  cur += '(';
  if (l > 0) generate_paren(result, cur, l - 1, r);
  cur.pop_back();
  // If there are fewer left parens, we can place a right paren and recurse
  cur += ')';
  if (r > 0 && l < r) generate_paren(result, cur, l, r - 1);
  cur.pop_back();
}

vector<string> generateParenthesis(int n) {
  int l(n);
  int r(n);  // Create Left and Right Parentheses;
  vector<string> result;
  string cur;
  generate_paren(result, cur, l, r);
  return result;
}

TEST_CASE("22_example1", "[22]") {
  auto input = 3;
  auto result = generateParenthesis(input);
  vector<string> correct = {"((()))", "(()())", "(())()", "()(())", "()()()"};
  REQUIRE(result == correct);
}
TEST_CASE("22_example2", "[22]") {
  auto input = 1;
  auto result = generateParenthesis(input);
  vector<string> correct = {"()"};
  REQUIRE(result == correct);
}
