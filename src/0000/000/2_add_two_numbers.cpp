// 2_add_two_numbers
// Nevin Zheng
// 7/31/21

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <utils.hpp>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
 public:
  static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    constexpr int kTen = 10;
    auto head = ListNode();
    auto* curr = &head;
    int carry = 0;
    while (l1 or l2) {
      auto x = l1 ? l1->val : 0;
      auto y = l2 ? l2->val : 0;
      int sum = x + y + carry;
      carry = sum / kTen;
      curr->next = new ListNode(sum % kTen);
      curr = curr->next;
      l1 = l1 ? l1->next : l1;
      l2 = l2 ? l2->next : l2;
    }
    if (carry) curr->next = new ListNode(carry);
    return head.next;
  }
};

TEST_CASE("2ex1", "[2]") {
  const vector<int> l1 = {2, 4, 3};
  const vector<int> l2 = {5, 6, 4};
  ListNode* result =
      Solution::addTwoNumbers(utils::makeList(l1), utils::makeList(l2));
  string ans = utils::toString(result);
  REQUIRE(ans == "7, 0, 8, ");
}

TEST_CASE("2ex2", "[2]") {
  const vector<int> l1 = {9, 9, 9, 9, 9, 9, 9};
  const vector<int> l2 = {9, 9, 9, 9};
  ListNode* result =
      Solution::addTwoNumbers(utils::makeList(l1), utils::makeList(l2));
  string ans = utils::toString(result);
  REQUIRE(ans == "8, 9, 9, 9, 0, 0, 0, 1, ");
}