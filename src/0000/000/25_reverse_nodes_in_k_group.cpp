//
// Created by Nevin Zheng on 7/18/21.
//
#include <catch2/catch.hpp>
#include <utils.hpp>
#include <vector>

using namespace std;

int countNodes(ListNode* head) {
  auto count = 0;
  while (head) {
    count++;
    head = head->next;
  }
  return count;
}

/**
 * We will solve this problem in a recursive fashion. You really need to draw
 * this out on a whiteboard At each stack fram we'll have head, p, q, and r ptrs
 * Carefully trace the code with paper and a diagram to understand
 * @param head
 * @param k
 * @return
 */
ListNode* reverseKGroup(ListNode* head, int k) {
  ListNode *p = head, *q(nullptr), *r(nullptr);
  auto size =
      countNodes(head);  // O(N) Call Per segment. Can refactor to pass as arg
  auto i(0);
  while (p and i < k) {  // Reversing the linked list
    r = q;
    q = p;
    p = p->next;
    q->next = r;
    i++;
  }
  if (p and size - i >= k) {
    head->next = reverseKGroup(p, k);
  } else {
    head->next = p;
  }
  return q;
}

class Solution {
 public:
  ListNode* getKth(ListNode* head, int k) {
    while (head and k--) {
      head = head->next;
    }
    return head;
  }

  ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(-1, head);
    auto* prev_group = &dummy;
    ListNode* next_group = nullptr;
    while (true) {
      // Get to the last element in the current group
      auto* kth = getKth(prev_group, k);
      if (!kth) return dummy.next;  // Last Group had fewer than k elements
      next_group = kth->next;

      // Reverse the group
      auto* prev = kth->next;
      auto* curr = prev_group->next;
      while (curr != next_group) {
        auto* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
      }
      auto* tmp = prev_group->next;
      prev_group->next = kth;
      prev_group = tmp;
    }
  }
};

TEST_CASE("25ex1", "[25]") {
  const vector<int> input = {1, 2, 3, 4, 5};
  auto k = 3;
  const vector<int> expected = {3, 2, 1, 4, 5};

  auto* input_list = utils::makeList(input);
  auto* expected_list = utils::makeList(expected);
  auto* result_list = reverseKGroup(input_list, k);

  REQUIRE(utils::compareList(result_list, expected_list));
}
