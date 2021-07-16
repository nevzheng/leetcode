//
// Created by Nevin Zheng on 7/15/21.
//
#include <vector>

#include "utils.hpp"

using namespace std;
ListNode *makeList(vector<int> a) {
    if (a.empty()) return nullptr;
    auto root = new ListNode(a.front());
    auto curr = root;
    for (auto i = 1; i < a.size(); i++) {
        curr->next = new ListNode(a[i]);
        curr = curr->next;
    }
    return root;
}

void printList(ListNode *head) {
    while (head) {
        cout << head->val << ", ";
        head = head->next;
    }
    cout << '\n';
}