// 1056_confusing_number
// Nevin Zheng
// 7/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

bool confusingNumber(int N) {
  const map<char, char> k_digits{
      {'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
  auto num = to_string(N);  // Convert to a string
  // all of the digits of the number have to be 0,1,6,8,9
  if (!all_of(cbegin(num), cend(num),
              [&k_digits](auto c) { return k_digits.count(c); })) {
    return false;
  }
  // Check for rotational symmetry. Number must be different
  string rotated;
  transform(crbegin(num), crend(num), back_inserter(rotated),
            [&k_digits](auto c) { return k_digits.at(c); });
  return num != rotated;
}

TEST_CASE("1056ex1", "[1056]") {
  // All of these are Confusing
  vector<int> conf{6,  9,  10, 16, 18, 19, 60, 61, 66, 68,
                   80, 81, 86, 89, 90, 91, 98, 99, 100};
  REQUIRE(all_of(begin(conf), end(conf),
                 [](const auto a) { return confusingNumber(a); }));
}

TEST_CASE("1056ex2", "[1056]") {
  // All of these are NOT Confusing
  vector<int> conf{77, 11, 888};
  REQUIRE(all_of(begin(conf), end(conf),
                 [](const auto a) { return !confusingNumber(a); }));
}