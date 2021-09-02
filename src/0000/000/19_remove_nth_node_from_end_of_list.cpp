// 19_remove_nth_node_from_end_of_list
// Nevin Zheng
// 8/29/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <utils.hpp>

using namespace std;

class Solution {
 public:
  static ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto* fast = head;
    auto* slow = head;
    // Len of List is n + (N-n)
    while (n--) fast = fast->next;  // Set fast to n
    if (!fast) return head->next;
    // Move Slow to N-n
    while (fast->next) fast = fast->next, slow = slow->next;
    // slow is now at correct position
    slow->next = slow->next->next;
    return head;
  }
};

TEST_CASE("19::1", "[19]") {
  auto five = make_unique<ListNode>(5);
  auto four = make_unique<ListNode>(4, five.get());
  auto three = make_unique<ListNode>(3, four.get());
  auto two = make_unique<ListNode>(2, three.get());
  auto one = make_unique<ListNode>(1, two.get());
  REQUIRE(Solution::removeNthFromEnd(one.get(), 2) != nullptr);
}

TEST_CASE("19::2", "[19]") {
  auto one = make_unique<ListNode>(1);
  REQUIRE(Solution::removeNthFromEnd(one.get(), 1) != nullptr);
}