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
    for (auto i = 1ul; i < a.size(); i++) {
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

bool compareList(ListNode *a, ListNode *b) {
    auto aLen(0), bLen(0);
    while (a and b) {
        if (a->val != b->val) return false;
        a = a->next;
        b = b->next;
    }
    return aLen == bLen;
}
