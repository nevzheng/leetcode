// 90_lru_cache
// Nevin Zheng
// 8/3/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class LRUCache {
 public:
  struct Item {
    int key;
    int value;
    Item(int key, int value) : key(key), value(value) {}
  };
  size_t capacity_;
  std::list<Item> items_;
  std::map<int, std::list<Item>::iterator> index_;

  explicit LRUCache(int capacity) : capacity_(capacity) {}

  int get(int key) {
    if (auto it = index_.find(key); it != end(index_)) {
      items_.splice(items_.begin(), items_, it->second);  // Splice to front
      return it->second->value;
    }
    return -1;
  }

  void update(int key, int val) {
    get(key);
    index_[key]->value = val;
  }

  void put(int key, int value) {
    if (index_.count(key)) return update(key, value);  // Update existing

    if (items_.size() == capacity_) {  // Pop LRU, insert front
      index_.erase(items_.back().key);
      items_.pop_back();
    }
    items_.emplace_front(key, value);
    index_.emplace(key, items_.begin());
  }
};

TEST_CASE("146ex1", "[146]") {
  auto lru = make_unique<LRUCache>(2);
  lru->put(1, 1);             // cache is {1=1}
  lru->put(2, 2);             // cache is {1=1, 2=2}
  REQUIRE(lru->get(1) == 1);  // return 1
  lru->put(3, 3);  // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  REQUIRE(lru->get(2) == -1);  // returns -1 (not found)
  lru->put(4, 4);  // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  REQUIRE(lru->get(1) == -1);  // return -1 (not found)
  REQUIRE(lru->get(3) == 3);   // return 3
  REQUIRE(lru->get(4) == 4);   // return 4
}

// ["LRUCache","put","put","get","put", "get","put","get","get","get"]
// [[2],       [1,0],[2,2],[1],   [3,3],[2],  [4,4], [1], [3],  [4]]

TEST_CASE("146ex2", "[146]") {
  auto lru = make_unique<LRUCache>(2);
  lru->put(1, 0);
  lru->put(2, 2);
  REQUIRE(lru->get(1) == 0);
  lru->put(3, 3);
  REQUIRE(lru->get(2) == -1);
  lru->put(4, 4);
  REQUIRE(lru->get(1) == -1);
  REQUIRE(lru->get(3) == 3);
  REQUIRE(lru->get(4) == 4);
}

//["LRUCache","put","put","put","put","get","get"]
//[[2],[2,1],[1,1],[2,3],[4,1],[1],[2]]
TEST_CASE("146ex3", "[146]") {
  auto lru = make_unique<LRUCache>(2);
  lru->put(2, 1);
  lru->put(1, 1);
  lru->put(2, 3);
  lru->put(4, 1);
  REQUIRE(lru->get(1) == -1);
  REQUIRE(lru->get(2) == 3);
}