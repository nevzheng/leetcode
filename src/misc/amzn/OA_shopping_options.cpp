// OA_shopping_options
// Nevin Zheng
// 8/13/21
/**
 * A customer wants to buy a pair of jeans, a pair of shoes, a skirt, and a top
but has a limited budget in dollars. Given different pricing options for each
product, determine how many options our customer has to buy 1 of each product.
You cannot spend more money than the budgeted amount.

Example
priceOfJeans = [2, 3]
priceOfShoes = [4]
priceOfSkirts = [2, 3]
priceOfTops = [1, 2]
budgeted = 10

The customer must buy shoes for 4 dollars since there is only one option. This
leaves 6 dollars to spend on the other 3 items. Combinations of prices paid for
jeans, skirts, and tops respectively that add up to 6 dollars or less are [2, 2,
2], [2, 2, 1], [3, 2, 1], [2, 3, 1]. There are 4 ways the customer can purchase
all 4 items.

Function Description

Complete the getNumberOfOptions function in the editor below. The function must
return an integer which represents the number of options present to buy the four
items.

getNumberOfOptions has 5 parameters:
int[] priceOfJeans: An integer array, which contains the prices of the pairs of
jeans available.
int[] priceOfShoes: An integer array, which contains the prices
of the pairs of shoes available.
int[] priceOfSkirts: An integer array, which
contains the prices of the skirts available.
int[] priceOfTops: An integer
array, which contains the prices of the tops available. int dollars: the total
number of dollars available to shop with.

Constraints

1 ≤ a, b, c, d ≤ 103
1 ≤ dollars ≤ 109
1 ≤ price of each item ≤ 109
Note: a, b, c and d are the sizes of the four price arrays
 */

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static int shoppingOptions(const vector<int>& A, const vector<int>& B,
                             const vector<int>& C, const vector<int>& D,
                             int budget) {
    vector<int> v1;
    vector<int> v2;
    int count = 0;
    for (auto a : A) {  // O(ab) time and space => O(N^2)
      for (auto b : B) {
        v1.push_back(a + b);
      }
    }
    for (auto c : C) {  // O(cd) time and space, => O(N^2)
      for (auto d : D) {
        v2.push_back(c + d);
      }
    }
    std::sort(v1.begin(), v1.end());  // O(N^2 lg(N^2)) => O(N^2 lg N)
    std::sort(v2.begin(), v2.end());  // O(N^2 lg(N^2)) => O(N^2 lg N)
    for (auto x : v1) {               // O(M) M = N^2 elements
      // O(lgN^2) => O(lg(N))
      auto it = std::upper_bound(v2.begin(), v2.end(), budget - x);
      if (it == v2.begin() || it == v2.end()) continue;
      count += static_cast<int>(std::distance(v2.begin(), it));
    }
    return count;
  }
};

TEST_CASE("oa::shopping_options::1", "[oa::shopping_options]") {
  vector<int> price_of_jeans = {2, 3};
  vector<int> price_of_shoes = {4};
  vector<int> price_of_skirts = {2, 3};
  vector<int> price_of_tops = {1, 2};
  const auto budgeted = 10;
  const auto expected = 4;
  REQUIRE(Solution::shoppingOptions(price_of_jeans, price_of_shoes,
                                    price_of_skirts, price_of_tops,
                                    budgeted) == expected);
}