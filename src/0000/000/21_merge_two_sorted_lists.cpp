// 21_merge_two_sorted_lists
// Nevin Zheng
// 8/10/21

#include "utils.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
using namespace std;

class Solution {
 public:
  static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1 and !l2) return nullptr;  // Both null
    if (l1 and !l2) return l1;        // Only l1
    if (!l1 and l2) return l2;        // Only l2
    ListNode head;
    auto* cur = &head;
    ListNode* next = nullptr;
    while (l1 || l2) {
      if (l1 and l2) {
        if (l1->val < l2->val) {
          next = l1;
          l1 = l1->next;
        } else {
          next = l2;
          l2 = l2->next;
        }
      } else if (l1) {
        next = l1;
        l1 = l1->next;
      } else {
        next = l2;
        l2 = l2->next;
      }
      cur->next = next;
      cur = cur->next;
    }
    return head.next;
  }
};

TEST_CASE("21ex1", "[21]") {
  vector<int> v1 = {1, 2, 4};
  vector<int> v2 = {1, 3, 4};
  vector<int> v3 = {1, 1, 2, 3, 4, 4};
  auto* l1 = utils::makeList(v1);
  auto* l2 = utils::makeList(v2);
  auto* l3 = utils::makeList(v3);
  auto* result = Solution::mergeTwoLists(l1, l2);
  utils::printList(result);
  REQUIRE(utils::compareList(result, l3));
}