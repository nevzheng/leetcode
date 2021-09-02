// 876_middle_of_linked_list
// Nevin Zheng
// 8/31/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <utils.hpp>

using namespace std;

class Solution {
 public:
  static int getLength(ListNode* head) {
    auto len = 0;
    while ((head = head->next)) ++len;
    return len;
  }

  static ListNode* traverse(ListNode* head, int count) {
    while (count--) head = head->next;
    return head;
  }

  ListNode* middleNode(ListNode* head) {
    auto len = getLength(head) / 2;
    return traverse(head, len);
  }
};