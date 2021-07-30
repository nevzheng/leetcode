// 677_map_sum_pairs
// Nevin Zheng
// 7/30/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * In this approach we keep two maps
 * The first map stores the full string and its associated value
 * the second map stores all possible prefixes and their current score
 * when a key is updated we need to subtract its current score and add its new
 * one.
 * This takes O(n^2) update O(1) sum. and space linear to the input size
 */
// class MapSum {
//  public:
//   map<string, int> prefixes_;
//   map<string, int> strings_;
//
//   MapSum() = default;
//
//   void insert(const string& key, int val) {
//     auto old_val = strings_.count(key) ? strings_.at(key) : 0;
//     strings_[key] = val;
//     string prefix;
//     for (char c : key) {
//       prefix += c;
//       prefixes_[prefix] = prefixes_[prefix] - old_val + val;
//     }
//   }
//
//   [[nodiscard]] int sum(const string& prefix) const {
//     return prefixes_.count(prefix) ? prefixes_.at(prefix) : 0;
//   }
// };

/**
 * In this solution we use a trie to more efficiently store prefixes
 * We accomplish O(K) time and memory where K is the length of the longest
 * input string
 */
class Node {
 public:
  static constexpr int kAsciiLowercaseCount = 26;
  int score_ = 0;
  vector<shared_ptr<Node>> children_;
  Node() : children_(kAsciiLowercaseCount) {}

  shared_ptr<Node>& getChild(char c) { return children_[c - 'a']; }
};

class MapSum {
  unordered_map<string, int> vals_;
  shared_ptr<Node> root_;

 public:
  MapSum() : root_(make_shared<Node>()) {}

  void insert(const string& key, int val) {
    auto delta = val - vals_[key];
    vals_[key] = val;  // Update/emplace value;
    auto cur = root_;
    cur->score_ += delta;
    for (auto c : key) {
      if (!cur->getChild(c)) cur->getChild(c) = make_shared<Node>();
      cur = cur->getChild(c);
      cur->score_ += delta;
    }
  }

  [[nodiscard]] int sum(const string& prefix) const {
    auto cur = root_;
    for (auto c : prefix) {
      cur = cur->getChild(c);
      if (!cur) return 0;
    }
    return cur->score_;
  }
};

TEST_CASE("677ex1", "[677]") {
  auto map_sum = make_unique<MapSum>();
  map_sum->insert("apple", 3);
  REQUIRE(map_sum->sum("ap") == 3);  // return 3 (apple = 3)
  map_sum->insert("app", 2);
  REQUIRE(map_sum->sum("ap") == 5);  // return 5 (apple + app = 3 + 2 = 5)
}