// 895_max_freq_stack
// Nevin Zheng
// 8/9/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class FreqStack {
 public:
  int max_freq_{};
  unordered_map<int, int> freq_;  // freqs_[key] = frequency of key
  // Each Stack contains elements with a certain frequency
  // items_[i] => elements with frequency of i
  // items_[0] is present but unused
  // map because vector has items_[0], which you need to work around
  map<int, stack<int>> items_;

  void push(int val) {
    auto new_f = ++freq_[val];          // Increment frequency of val
    max_freq_ = max(max_freq_, new_f);  // Get Max Freq
    items_[new_f].push(val);            // Push onto appropriate stack
  }

  int pop() {
    auto ret = items_[max_freq_].top();  // Stash return val
    --freq_[ret];                        // decrement frequency
    items_[max_freq_].pop();             // Pop element
    if (items_[max_freq_].empty()) {
      items_.erase(max_freq_);
      --max_freq_;
    }
    return ret;
  }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */

TEST_CASE("895ex1", "[895]") {
  FreqStack freq_stack;
  freq_stack.push(5);              // The stack is [5]
  freq_stack.push(7);              // The stack is [5,7]
  freq_stack.push(5);              // The stack is [5,7,5]
  freq_stack.push(7);              // The stack is [5,7,5,7]
  freq_stack.push(4);              // The stack is [5,7,5,7,4]
  freq_stack.push(5);              // The stack is [5,7,5,7,4,5]
  REQUIRE(freq_stack.pop() == 5);  // return 5, as 5 is the most frequent. The
                                   // stack becomes [5,7,5,7,4].
  // return 7, as 5 and 7 is the most frequent, but 7 is
  // closest to the top. The stack becomes [5,7,5,4].
  REQUIRE(freq_stack.pop() == 7);
  REQUIRE(freq_stack.pop() == 5);  // return 5, as 5 is the most frequent. The
                                   // stack becomes [5,7,4].
  // return 4, as 4, 5 and 7 is the most frequent, but 4 is
  // closest to the top. The stack becomes [5,7].
  REQUIRE(freq_stack.pop() == 4);
}
