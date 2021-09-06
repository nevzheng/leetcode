// 1629_slowest_key
// Nevin Zheng
// 9/6/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static char slowestKey(const vector<int>& releaseTimes,
                         const string& keysPressed) {
    vector<int> durations;
    durations.reserve(releaseTimes.size());
    std::adjacent_difference(releaseTimes.cbegin(), releaseTimes.cend(),
                             back_inserter(durations));
    auto idx = 0UL;
    char mx = keysPressed.front();
    for (auto i = 0UL; i < durations.size(); ++i) {
      if (durations[i] > durations[idx] ||
          (durations[i] == durations[idx] &&
           keysPressed[i] > keysPressed[idx])) {
        idx = i;
        mx = keysPressed[idx];
      }
    }
    return mx;
  }
};

TEST_CASE("1629::1", "[1629]") {
  const vector<int> release_times{9, 29, 49, 50};
  const string keys_pressed = "cbcd"s;
  const char expected = 'c';
  REQUIRE(Solution::slowestKey(release_times, keys_pressed) == expected);
}

TEST_CASE("1629::2", "[1629]") {
  const vector<int> release_times{23, 34, 43, 59, 62, 80, 83, 92, 97};
  const string keys_pressed = "qgkzzihfc"s;
  const char expected = 'q';
  REQUIRE(Solution::slowestKey(release_times, keys_pressed) == expected);
}