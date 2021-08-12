// 877_stone_game
// Nevin Zheng
// 8/5/21

#include <bits/stdc++.h>
using namespace std;

/**
 * The Sum of the stones is always odd
 * There are always an even number of piles.
 * Alex, who always goes first, can always take the max of L and R piles
 * and will always end up with more stones.
 * The Base Cases are:
 * 1 pile: Alex will always win.
 * 2 Piles: sum is odd, so one pile has to have more. Alex can take max
 * All other cases will reduce to 2 or 1
 * Thus Alex always wins
 */
// class Solution {
//  public:
//   bool stoneGame(vector<int>& piles) {
//     return true;
//   }
// };

/**
 * A and L's scores are complementary s.t
 * let A = alex score, L = Lee score, S = sum of all piles
 * L = S - A. minimizing lee's score, maximizes Alex's
 * let dp[i][j] = value of game with piles (i..j) , w.r.t alex's score
 * There are two players. we can compute the turn id from the parity w/ (i-j)%2
 *
 * On Alex's turn we want to maximize the score. Alex has odd parity
          dp[i + 1][j + 1] =
              max(piles[i] + dp[i + 2][j + 1], piles[j] + dp[i + 1][j]);
 * On Lee's turn we want to minimize the score. Lee has even parity
          dp[i + 1][j + 1] =
              min(-piles[i] + dp[i + 2][j + 1], -piles[j] + dp[i + 1][j]);
 * Each move shrinks the remaining partition.
 *
 * At the end we return dp[1][p_len]
 * O(n^2) time and space
 */
class Solution {
 public:
  static bool stoneGame(vector<int>& piles) {
    auto p_len = piles.size();
    // dp[i+1][j+1] = the value of the game [piles[i], ..., piles[j]]
    vector dp(p_len + 1, vector(p_len + 2, 0));

    for (auto len = 1UL; len <= p_len; ++len) {
      for (auto i = 0UL, j = len - 1; j < p_len; ++i, ++j) {
        // j - i - N; but +x = -x (mod 2)
        auto parity = (j + i + p_len) % 2;
        if (parity) {  // Alex's turn
          dp[i + 1][j + 1] =
              max(piles[i] + dp[i + 2][j + 1], piles[j] + dp[i + 1][j]);
        } else {
          dp[i + 1][j + 1] =
              min(-piles[i] + dp[i + 2][j + 1], -piles[j] + dp[i + 1][j]);
        }
      }
    }
    return dp[1][p_len] > 0;
  }
};
