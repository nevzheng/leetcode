// split_linked_list_in_parts
// Nevin Zheng
// 9/29/21

#include <catch2/catch.hpp>
#include <utils.hpp>

using namespace std;

class Solution {
 public:
  static int getLength(ListNode* head) {
    if (!head) return 0;
    auto len = 0;
    while (head) {
      head = head->next;
      ++len;
    }
    return len;
  }

  vector<ListNode*> splitListToParts(ListNode* head, int k) {
    auto len = getLength(head);
    auto subLen = len / k;  // Each sublist will have len/k parts
    // there may be a remainder which need to be distributed among the first
    // (len%k) elements extending their lengths by 1
    auto rem = len % k;
    auto* cur = head;
    vector<ListNode*> ans(k);       // answer is k lists, some may be null;
    for (auto i = 0; i < k; ++i) {  // Create k lists
      auto remaining = subLen;      // len of this sublist
      if (rem > 0) {                // maybe distribute a remainder to sublist
        ++remaining;
        --rem;
      }
      ans[i] = cur;  // place head in answer
      // splice the sublist
      ListNode* prev = nullptr;
      // traverse the no. of nodes that will be assigned
      while (remaining--) {
        prev = cur;
        cur = cur->next;
      }
      if (prev) prev->next = nullptr;  // end the list
    }
    return ans;
  }
};