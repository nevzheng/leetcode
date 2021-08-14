//
// Created by Nevin Zheng on 7/15/21.
//
#include "../include/utils.hpp"
#include <vector>

using namespace std;

namespace utils {
ListNode* makeList(vector<int> a) {
  if (a.empty()) return nullptr;
  auto* root = new ListNode(a.front());
  auto* curr = root;
  for (auto i = 1UL; i < a.size(); i++) {
    curr->next = new ListNode(a[i]);
    curr = curr->next;
  }
  return root;
}

void printList(ListNode* head) {
  while (head) {
    cout << head->val << ", ";
    head = head->next;
  }
  cout << '\n';
}

string toString(ListNode* head) {
  string ans;
  while (head) {
    ans += to_string(head->val) + ", ";
    head = head->next;
  }
  return ans;
}

bool compareList(ListNode* a, ListNode* b) {
  auto a_len(0UL);
  auto b_len(0UL);
  while (a and b) {
    if (a->val != b->val) return false;
    a = a->next;
    b = b->next;
    ++a_len;
    ++b_len;
  }
  return a_len == b_len;
}
}  // namespace utils