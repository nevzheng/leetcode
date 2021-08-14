// 14_longest_common_prefix
// Nevin Zheng
// 7/31/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static string longestCommonPrefix(const vector<string>& strs) {
    string lcp;
    // Find the shortest string in the array
    auto shortest = *std::min_element(
        strs.begin(), strs.end(),
        [](const auto& x, const auto& y) { return x.size() < y.size(); });

    for (auto i = 0UL; i < shortest.size(); i++) {
      auto c = shortest[i];
      for (const auto& w : strs) {
        if (w.at(i) != c) return lcp;
      }
      lcp += c;
    }
    return lcp;
  }
};

TEST_CASE("14ex1", "[14]") {
  const vector strs{"flower"s, "flow"s, "flight"s};
  const auto expected = "fl"s;
  REQUIRE(Solution::longestCommonPrefix(strs) == expected);
}

TEST_CASE("14ex2", "[14]") {
  const vector strs{"dog"s, "racecar"s, "car"s};
  const auto expected = ""s;
  REQUIRE(Solution::longestCommonPrefix(strs) == expected);
}