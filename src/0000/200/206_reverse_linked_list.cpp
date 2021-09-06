// 206_reverse_linked_list
// Nevin Zheng
// 9/6/21

#include "utils.hpp"

using namespace std;

class Solution {
 public:
  static ListNode* reverseList(ListNode* head) {
    ListNode* cur{head};
    ListNode* pre{nullptr};
    while (cur) {
      auto* nxt = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nxt;
    }
    return pre;
  }
};