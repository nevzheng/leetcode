// 850_rectangle_area_2
// Nevin Zheng
// 8/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  using Interval = tuple<int, int>;
  const static int64_t kMod = 1e9 + 7;
  enum class EventType { kOpen, kClose };
  struct Event {
    int x;
    EventType type;
    int y1;
    int y2;
    Event(int x, EventType type, int y1, int y2)
        : x(x), type(type), y1(y1), y2(y2) {}
  };

  static int64_t getArea(int64_t width, const multiset<Interval>& intervals) {
    auto area = 0LL;
    auto prev = 0LL;
    for (const auto& [bot, top] : intervals) {
      auto bt = max(static_cast<int64_t>(prev), static_cast<int64_t>(bot));
      if (top > bt) {
        area += (top - bt) * width;
        prev = top;
      }
    }
    return area;
  }

  static int rectangleArea(const vector<vector<int>>& rectangles) {
    vector<Event> events;
    for (const auto& r : rectangles) {
      const auto& [x1, y1, x2, y2] = tie(r[0], r[1], r[2], r[3]);
      events.emplace_back(x1, EventType::kOpen, y1, y2);
      events.emplace_back(x2, EventType::kClose, y1, y2);
    }
    auto ans = 0LL;
    auto prev_x = 0LL;
    // must allow duplicates
    multiset<Interval> intervals;
    // Sort by increasing x to process events in increasing x
    std::sort(begin(events), end(events),
              [](const auto& a, const auto& b) { return a.x < b.x; });
    for (const auto& [cur_x, type, y1, y2] : events) {
      ans += getArea(cur_x - prev_x, intervals);
      if (type == EventType::kOpen) {
        intervals.insert({y1, y2});
      } else {
        intervals.erase(intervals.find({y1, y2}));
      }
      prev_x = cur_x;
    }
    return static_cast<int>(ans % kMod);
  }
};

TEST_CASE("850::1", "[850]") {
  const vector<vector<int>> rectangles{
      {0, 0, 2, 2}, {1, 0, 2, 3}, {1, 0, 3, 1}};
  const auto expected = 6;
  REQUIRE(Solution::rectangleArea(rectangles) == expected);
}

TEST_CASE("850::2", "[850]") {
  const vector<vector<int>> rectangles{{0, 0, 1000000000, 1000000000}};
  const auto expected = 49;
  REQUIRE(Solution::rectangleArea(rectangles) == expected);
}

TEST_CASE("850::3", "[850]") {
  const vector<vector<int>> rectangles{
      {0, 0, 3, 3}, {2, 0, 5, 3}, {1, 1, 4, 4}};
  const auto expected = 18;
  REQUIRE(Solution::rectangleArea(rectangles) == expected);
}