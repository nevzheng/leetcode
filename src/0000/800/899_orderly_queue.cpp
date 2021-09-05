// 899_orderly_queue
// Nevin Zheng
// 9/5/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * If k is 0 no rotation is possible
 * If we have k=1, then that's equivalent to a left rotation of the string.
 * if k is 1, we'll just left rotate the minimum char to the front
 * For k is 2, after manipulating the string, we realize that this enables
 * swapping adjacent characters.
 * for k>2, k=2 is included
 * so k>=2 results in the sorted string
 */
class Solution {
 public:
  static string orderlyQueue(const string& s, int k) {
    if (k == 0) return s;  // no move possible
    auto cur = s;
    // Rotate Min Element to front
    if (k == 1)
      std::rotate(cur.begin(), std::min_element(cur.begin(), cur.end()),
                  cur.end());
    if (k >= 2) std::sort(cur.begin(), cur.end());
    return cur;
  }
};

TEST_CASE("899::1", "[899]") {
  const auto s = "cba"s;
  const auto k = 1;
  const auto expected = "acb"s;
  REQUIRE(Solution::orderlyQueue(s, k) == expected);
}

TEST_CASE("899::2", "[899]") {
  const auto s = "baaca"s;
  const auto k = 3;
  const auto expected = "aaabc"s;
  REQUIRE(Solution::orderlyQueue(s, k) == expected);
}

TEST_CASE("899::3", "[899]") {
  const auto s = "xmvzi"s;
  const auto k = 2;
  const auto expected = "imvxz"s;
  REQUIRE(Solution::orderlyQueue(s, k) == expected);
}
