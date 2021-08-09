// 70_climbing_stairs
// Nevin Zheng
// 8/9/21
// Follow-up Questions:
//
// Write algorithm for variable number that can be climbed at each step (what if
// we could jump two stairs?)
// Write algorithm that tells us number of ways to arrive at last step for each
// leg (number of ways that end with left leg vs. right)
// Now consider a variable number of legs.

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * If we draw out a diagram, we can derive a recurrence relationship
 * for the number of ways to arrive at a given step.
 * This is given by the nth Fibonacci number.
 * There are several formulas for computing the nth Fibonacci number
 * The simple recursive formula is not efficient, adding memoization helps.
 * A better method is with dynamic programming. The downside is that it
 * requires linear memory.
 * the best method is in linear memory and constant time with two variables
 * other methods include compile time computation with a static table
 */
// class Solution {
//  public:
//   static int climbStairs(int n) {
//     if (n < 2) return n;  // F(0) = 0, F(1) = 1
//     int f0 = 0;
//     int f1 = 1;
//     for (auto i = 0; i < n; ++i) {
//       auto tmp = f0 + f1;
//       f0 = f1;
//       f1 = tmp;
//     }
//     return f1;
//   }
// };
//
// TEST_CASE("70ex1", "[70]") {
//   const auto n = 2;
//   const auto expected = 2;
//   REQUIRE(Solution::climbStairs(n) == expected);
// }
//
// TEST_CASE("70ex2", "[70]") {
//   const auto n = 3;
//   const auto expected = 3;
//   REQUIRE(Solution::climbStairs(n) == expected);
// }

/**
 * The first followup question asks us to consider a variable number of hops
 * we could previously take only one or 2 steps.
 * We can use dynamic programming to formulate an answer. At each iteration
 * we will need to sum up the last s steps. Given a number of steps s
 * A simple Implementation will use O(s*N) time and O(s) space.
 * We can also be given an arbitrary set of steps, EX {1, 3, 5 } and iterate
 * over them.
 *
 * The best implementation of this will have a complexity of O(s*N) time and
 * O(s) space. Only the last s values of the dp array need to be kept,
 * but the implementation will be slightly more complex since you need to
 * maintain only the last s steps. If we're given a set of steps, we can still
 * use only O(s) space as long as we implement proper book keeping.
 *
 * For simplicity I'll implement the linear space first.
 *
 * Regarding base cases, Let's try stating the recurrence relation as
 * F(n) = F(n-i) for i in 1..=s
 * if n-i < 0 the F(n-i) = 0
 * Regarding Base Cases, the number of ways to reach a step in 0..=s is going
 * to be composition of 1 (taking s steps) as well as summing the numbers before
 * it. we'll place a 1 at dp[i] for i in 1..=s, and then the iteration should
 * fill it it from there
 */
// class Solution {
//  public:
//   /**
//    * Counts the number of ways to climb to the top of a staircase of n steps
//    * if you can take at most s steps
//    * @param n
//    * @param s The maximum number of steps
//    * @return
//    */
//   static int climbStairs(int n, int s) {
//     vector<int> dp(n + 1);  // dp from 0 to n
//     std::fill_n(dp.begin()+1, s, 1);
//     for (auto i = 0; i < n; ++i) {
//       for (auto j = 1; j <= s; ++j) {
//         dp[i] += (i - j) >= 0 ? dp[i - j] : 0;
//       }
//     }
//     return dp.back();
//   }
// };

/**
 * In this variation we can only take any of a given number of steps
 * We apply the same logic as above.
 */
// class Solution {
//  public:
//   /**
//    * Counts the number of ways to climb to the top of a staircase of n steps
//    * if you can only take steps from s
//    * @param n
//    * @param s The number of steps in s
//    * @return
//    */
//   static int climbStairs(int n, vector<int> steps) {
//     vector<int> dp(n + 1);  // dp from 0 to n
//     for (auto s : steps) dp[s] = 0;
//     for (auto i = 0; i < n; ++i) {
//       for (auto s : steps) dp[i] += (i - s) >= 0 ? dp[i - s] : 0;
//     }
//     return dp.back();
//   }
// };

/**
 * The third follow up question asks us to consider whether we'll land on the
 * left or right leg. We first need to define what we mean by right or left leg
 * Let's say that it represents the parity of the number of steps taken
 * to reach a given step. So an even number of steps vs an odd number of steps.
 * To do this we will need TWO dp arrays. Each array will track a given
 * parity and we will update our recurrence to be a pair.
 * Let LEFT be even
 * and RIGHT be odd
 * DP_L[n] = DP_R[n-1] + DP_L[n-2];
 * DP_R[n] = DP_R[n-2] + DP_L[n-1];
 * Regarding Base Cases we should be able to use F(0) = 0 and F(1) = 1
 * but F(0) will be in the left/even array and F(1) will be in the right/odd
 * array
 * The algorithm will take O(N) space and time
 * We could use constant space as we only need to track the last two values
 * from each array, but again the implementation might be a bit more involved.
 */
// class Solution {
//  public:
//   /**
//    * Counts the number of ways to climb to the top of a staircase of n steps
//    * if you can only take steps from s
//    * @param n
//    * @param s The number of steps in s
//    * @return
//    */
//   static pair<int, int> climbStairs(int n) {
//     vector<int> dp_l(n + 1);  // left, even
//     vector<int> dp_r(n + 1);  // right, odd
//     dp_r[1] = 1;
//     for (auto i = 2; i < n; ++i) {
//       dp_l[i] = dp_r[i - 1] + dp_l[i - 2];
//       dp_r[i] = dp_r[i - 2] + dp_l[i - 1];
//     }
//     return {dp_l.back(), dp_r.back()};
//   }
// };

/**
 * This variation asks us to consider a variable number of legs.
 * Who's climbing these stairs? an octopus?
 * Jokes aside, we can extend our thinking from the bipedal case.
 * We can allocate a number of arrays proportional to the number of legs
 * then rewrite our recurrences. For each value of i, F_k(i) will take
 * contributions from previous values if the step is possible
 * So if we had a seventh leg it would be:
 * F_7[i] = F_6(i-1) + F_5(i-2) + F_4(i-3) + F_3(i-4) + F_2(i-5) + F_1(i-6)
 *
 * We can do this in O(l*n) time and O(l*n) space where l is the number of legs
 * Again we could use an amount of space linear to the number of legs, but
 * implementing it is more involved.
 *
 *
 * There's also a really cool trick with these where we can express our
 * state transitions as matrices and use matrix techniques to come
 * up with more efficient solutions.
 */
// class Solution {
//  public:
//   /**
//    * Counts the number of ways to climb to the top of a staircase of n steps
//    * if you can only take steps from s
//    * @param n
//    * @param s The number of steps in s
//    * @return
//    */
//   static pair<int, int> climbStairs(int n, int l) {
//     // Ignore l_0, which would be the zeroth leg.
//     vector<vector<int>> dp(l + 1, vector<int>(n + 1));
//     vector<int> dp_l(n + 1);  // left, even
//     vector<int> dp_r(n + 1);  // right, odd
//     dp_r[1] = 1;
//     for (auto i = 2; i < n; ++i) {
//     }
//
//     return {dp_l.back(), dp_r.back()};
//   }
// };
