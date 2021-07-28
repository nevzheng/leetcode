// 932_beautiful_array
// Nevin Zheng
// 7/28/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * For This problem, lets see if we can build solutions from previous solutions.
 * For Example, 1,3,2 is a valid beautiful array (BA)
 * Can we create BA_4 from BA_3 by appending and prepending 4? No This doesn't
 * work. We'll have to try a different solution. In construction problems
 * if appending and prepending doesn't work, you can try to figure out a
 * divide and conquer approach.
 * In the formula 2*ak = ai + aj, we notice that in order for the formula to be
 * satisfied. ai and aj need to have the same parity. It doesn't mean that
 * if they have the same parity then the equation is correct. However, if they
 * have different parity then its impossible. This is a useful observation.
 * Another useful observation is that multiply the elements of a beautiful
 * array does not affect its beauty.
 * EX: [1,3,2] *2 => [2,6,4] is still beautiful. Try for other arrays
 * to get a feel for it. That means we can multiply by 2 and still have a valid
 * BA.
 * Another Property is that adding a constant to each element doesn't change its
 * beauty. So [1,3,2] -> [2,4,3] is still beautiful. Try for other arrays.
 * Interesting constants to add are 1 and -1. We'll see why in a bit.
 * A third interesting property is if we concatenate two beautiful
 * arrays, then the resulting array will be beautiful.
 * Given this four properties, we should be able to construct beautiful arrays
 * of arbitrary length.
 * For a BA of length N, we can create an BA of length 2N
 * The first array results in the odd numbers and the second results in the
 * evens for the given range.
 * multiplication nad addition don't affect beauty as demonstrated
 * concatenation of two BAs results in a BA
 * by applying [2*n-1 for n in A] + [2*n for n in A] we can get a length 2n
 * n isn't always an even number though. we can fix this by
 * making the even array f(n/2) and the odd f(n/2 + n%2)
 * For n =5, this gets us f(2) and f(3) concatenated together
 * for n = 0, the BA is [] empty
 * for n = 1, the BA is [1].
 * for n = 2, the BA is [1,2]
 * for n = 3, the BA is [1,3,2]
 * for n = 4, the BA is [1,3,2,4]
 * for n = 5, the BA is [1,5,3,2,4]
 *
 * If we draw out the recursion tree we see that a naive implementation
 * gets us O(nlgn) time and O(n*2n) memory. However, with caching
 * we can reduce this to O(n) time nad O(n^2) memory
 * There are some additional c++ tricks we can apply to speed up performance
 * like returning references to elements in the cache to avoid copying.
 * and preallocating memory when forming the new entry
 */
class Solution {
  map<int, vector<int>> cache_;

  vector<int>& construct(int n) {
    if (cache_.count(n)) return cache_.at(n);
    if (n == 0) return cache_[0] = {};
    if (n == 1) return cache_[1] = {1};
    auto& odds = construct((n / 2) + (n % 2));
    auto& evens = construct((n / 2));
    auto& ans = cache_[n];
    ans.reserve(n);  // preallocate
    transform(begin(odds), end(odds), back_inserter(ans),
              [](auto x) { return 2 * x - 1; });
    transform(begin(evens), end(evens), back_inserter(ans),
              [](auto x) { return 2 * x; });
    return ans;
  }

 public:
  vector<int> beautifulArray(int n) { return construct(n); }
};

TEST_CASE("932ex0", "[932]") {
  const auto n = 0;
  const vector<int> expected = {};
  REQUIRE(Solution().beautifulArray(n) == expected);
}

TEST_CASE("932ex1", "[932]") {
  const auto n = 1;
  const vector expected = {1};
  REQUIRE(Solution().beautifulArray(n) == expected);
}

TEST_CASE("932ex2", "[932]") {
  const auto n = 2;
  const vector expected = {1, 2};
  REQUIRE(Solution().beautifulArray(n) == expected);
}

TEST_CASE("932ex3", "[932]") {
  const auto n = 3;
  const vector expected = {1, 3, 2};
  REQUIRE(Solution().beautifulArray(n) == expected);
}

TEST_CASE("932ex4", "[932]") {
  const auto n = 4;
  const vector expected = {1, 3, 2, 4};
  REQUIRE(Solution().beautifulArray(n) == expected);
}

TEST_CASE("932ex5", "[932]") {
  const auto n = 5;
  const vector expected = {1, 5, 3, 2, 4};
  REQUIRE(Solution().beautifulArray(n) == expected);
}
