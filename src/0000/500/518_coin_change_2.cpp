class Solution {
 public:
  int change(int W, vector<int>& A) {
    std::vector<int> dp(W + 1);
    dp[0] = 1;
    // For Each coin, count number of ways to  make any w
    for (auto x : A) {
      for (auto w = 0; w <= W; ++w) {
        if (w - x >= 0) dp[w] += dp[w - x];
      }
    }
    return dp.back();
  }
};