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
  static ListNode* removeNthFromEnd(ListNode* head, int n) {}
};

TEST_CASE("19::1", "[19]") {
  auto five = make_unique<ListNode>(5);
  auto four = make_unique<ListNode>(4, five.get());
  auto three = make_unique<ListNode>(3, four.get());
  auto two = make_unique<ListNode>(2, three.get());
  auto one = make_unique<ListNode>(1, two.get());
  REQUIRE(Solution::removeNthFromEnd(one) != nullptr);
}