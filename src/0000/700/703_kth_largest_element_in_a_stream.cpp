// 703_kth_largest_element_in_a_stream
// Nevin Zheng
// 7/31/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class KthLargest {
 public:
  size_t k_;
  std::priority_queue<int, vector<int>, greater<>> pq_;  // min heap
  KthLargest(size_t k, vector<int>&& nums) : k_(k) {
    for (auto& val : nums) add(val);
  }

  int add(int val) {
    if (pq_.size() < k_) {
      pq_.push(val);
    } else if (val > pq_.top()) {
      pq_.pop();
      pq_.push(val);
    }
    return pq_.top();
  }
};

TEST_CASE("703ex1", "[703]") {
  KthLargest kl(3, {4, 5, 8, 2});
  REQUIRE(kl.add(3) == 4);
  REQUIRE(kl.add(5) == 5);
  REQUIRE(kl.add(10) == 5);
  REQUIRE(kl.add(9) == 8);
  REQUIRE(kl.add(4) == 8);
}