// 1057_campus_bikes
// Nevin Zheng
// 8/4/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

struct Position {
  int x;
  int y;
  Position() = default;
  Position(int x, int y) : x(x), y(y) {}
  explicit Position(const vector<int>& v) : x(v.front()), y(v.back()) {}
};

struct Pairing {
  size_t w_idx;
  size_t b_idx;
  Position worker;
  Position bike;
  Pairing(size_t w_idx, size_t b_idx, const vector<int>& worker,
          const vector<int>& bike)
      : w_idx(w_idx), b_idx(b_idx), worker(worker), bike(bike) {}
  [[nodiscard]] int manhattan_distance() const {
    return std::abs(bike.x - worker.x) + std::abs(bike.y - worker.y);
  }
  [[nodiscard]] size_t worker_index() const { return w_idx; }
  [[nodiscard]] size_t bike_index() const { return b_idx; }
};

/**
 * In this solution we will generate all possible pairings of bikes and
 * workers and then place them into a priority queue which will
 * output the pair with the minimum manhattan distance, breaking ties
 * with the given index criteria. We will pop pairings and make assignments
 * skipping any conflicts.
 * Creating the cartesian product is O(MN) and O(MN) space
 * Heapify-ing the product is O(MN) time and space
 * Then making the assignments is at worst O(MN LG(MN)) time
 */
class Solution {
 public:
  static vector<int> assignBikes(const vector<vector<int>>& workers,
                                 const vector<vector<int>>& bikes) {
    // Generate all possible Pairings O(W*B) time and space
    vector<Pairing> pairings;
    for (auto i = 0UL; i < workers.size(); ++i) {
      for (auto j = 0UL; j < bikes.size(); ++j) {
        pairings.emplace_back(i, j, workers[i], bikes[j]);
      }
    }

    // Create a priority queue with custom comparator
    auto cmp = [](const Pairing& a, const Pairing& b) {
      if (a.manhattan_distance() != b.manhattan_distance()) {
        return a.manhattan_distance() > b.manhattan_distance();
      }
      if (a.worker_index() != b.worker_index()) {
        return a.worker_index() > b.worker_index();
      }
      return a.bike_index() > b.bike_index();
    };
    std::priority_queue pq(cmp, pairings);

    vector<int> assignments(workers.size());
    set<size_t> w_remaining;
    set<size_t> b_remaining;
    for (auto i = 0UL; i < workers.size(); ++i) {
      w_remaining.insert(i);
      b_remaining.insert(i);
    }

    while (!w_remaining.empty()) {
      auto cur = pq.top();
      pq.pop();
      if (w_remaining.count(cur.worker_index()) == 0UL ||
          b_remaining.count(cur.bike_index()) == 0UL) {
        continue;
      }
      w_remaining.erase(cur.worker_index());
      b_remaining.erase(cur.bike_index());
      assignments[cur.worker_index()] = static_cast<int>(cur.bike_index());
    }
    return assignments;
  }
};

TEST_CASE("1057ex1", "[1057]") {
  const vector<vector<int>> workers = {{0, 0}, {2, 1}};
  const vector<vector<int>> bikes = {{1, 2}, {3, 3}};
  const vector<int> expected = {1, 0};
  REQUIRE(Solution::assignBikes(workers, bikes) == expected);
}

TEST_CASE("1057ex2", "[1057]") {
  const vector<vector<int>> workers = {{0, 0}, {1, 1}, {2, 0}};
  const vector<vector<int>> bikes = {{1, 0}, {2, 2}, {2, 1}};
  const vector<int> expected = {0, 2, 1};
  REQUIRE(Solution::assignBikes(workers, bikes) == expected);
}