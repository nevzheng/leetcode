// 72_edit_distance
// https://turnerj.com/blog/levenshtein-distance-part-2-gotta-go-fast
// Optimizations
// Can trim common prefix and suffix. Great for strings which are close\
// Can reduce memory. Only need two rows, can structure to only use
// last two rows.
// Actually only need three cells. Can optimize further.
// Nevin Zheng
// 8/4/21
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * A Variadic Min function
 * @tparam T1
 * @tparam T2
 * @tparam Tail
 * @param t1
 * @param t2
 * @param tail
 * @return
 */
template <typename T1, typename T2, typename... Tail>
constexpr auto min(T1&& t1, T2&& t2, Tail&&... tail) {
  if constexpr (sizeof...(tail) == 0) {
    return t1 < t2 ? t1 : t2;
  } else {
    return min(min(t1, t2), tail...);
  }
}
class Solution {
 public:
  static int minDistance(const string& a, const string& b) {
    auto len_a = static_cast<int>(a.size());
    auto len_b = static_cast<int>(b.size());
    vector dp(len_a + 1, vector(len_b + 1, 0));
    for (auto i = 0; i <= len_a; i++) {
      for (auto j = 0; j <= len_b; j++) {
        if (i == 0) {  // Base Case, a is empty. Replace all of a
          dp[i][j] = j;
        } else if (j == 0) {  // Base Case, b is empty, Replace all of b
          dp[i][j] = i;
        } else if (a[i - 1] == b[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];  // Chars are same, carry min forward
        } else {  // General. Select min between replace sub, delete
          dp[i][j] = 1 + min(dp[i][j - 1],       // Insert
                             dp[i - 1][j],       // Remove
                             dp[i - 1][j - 1]);  // Replace
        }
      }
    }
    return dp.back().back();
  }
};

TEST_CASE("72ex1", "[72]") {
  const auto word1 = "horse"s;
  const auto word2 = "ros"s;
  const auto expected = 3;
  REQUIRE(Solution::minDistance(word1, word2) == expected);
}

TEST_CASE("72ex2", "[72]") {
  const auto word1 = "intention"s;
  const auto word2 = "execution"s;
  const auto expected = 5;
  REQUIRE(Solution::minDistance(word1, word2) == expected);
}
