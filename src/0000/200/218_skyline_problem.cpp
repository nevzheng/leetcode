// 218_skyline_problem
// Nevin Zheng
// 8/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * To solve this problem we can use the "Line Scan" algorithm template
 * We can imagine each rectangle as a height with an on and off switch
 * the left means its active and the right means its inactive
 * We can envision a skyline as the interaction between many such rectangles
 * We will create a map<int,vector<Event>> that will keep track of what
 * heights are active/inactive for any given x
 * We then will process the x axis in increasing order of x
 * if a height is active we will insert it into the active heights
 * if its inactive we will remove it
 * for each x we will process all available events then try to extend the
 * skyline the new height will be 0 if the heights set is empty else it will be
 * the max value the skyline can only be extended if the new height is different
 * that the old height
 */
class Solution {
 public:
  enum class EventType {
    kOpen,
    kClose,
  };

  struct Event {
    EventType type;
    int height;
    Event(EventType type, int height) : type(type), height(height) {}
  };

  static vector<vector<int>> getSkyline(const vector<vector<int>>& buildings) {
    map<int, vector<Event>> map;  // Each position/x has events
    vector<vector<int>> skyline;
    for (const auto& b : buildings) {
      auto [L, R, H] = tie(b[0], b[1], b[2]);
      map[L].emplace_back(EventType::kOpen, H);   // Activate height
      map[R].emplace_back(EventType::kClose, H);  // Deactivate height
    }
    multiset<int> heights;  // Set of active heights. need duplicates
    for (auto& [pos, events] : map) {
      for (auto& [type, height] : events) {  // Process events for height
        type == EventType::kOpen ? heights.insert(height)
                                 : heights.erase(heights.find(height));
      }
      auto new_height =
          heights.empty() ? 0 : *heights.rbegin();  // 0 or max Hgt
      if (!skyline.empty() && skyline.back()[1] == new_height) continue;
      skyline.push_back({pos, new_height});  // Add a new point to height
    }
    return skyline;
  }
};

TEST_CASE("218::1", "[218]") {
  const vector<vector<int>> buildings{
      {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
  const vector<vector<int>> expected{{2, 10},  {3, 15}, {7, 12}, {12, 0},
                                     {15, 10}, {20, 8}, {24, 0}};
  REQUIRE(Solution().getSkyline(buildings) == expected);
}

TEST_CASE("218::2", "[218]") {
  const vector<vector<int>> buildings{{0, 2, 3}, {2, 5, 3}};
  const vector<vector<int>> expected{{0, 3}, {5, 0}};
  REQUIRE(Solution().getSkyline(buildings) == expected);
}