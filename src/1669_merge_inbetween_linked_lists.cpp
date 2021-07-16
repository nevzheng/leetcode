//
// Created by Nevin Zheng on 7/15/21.
//
// Definition for singly-linked list.

#include <catch2/catch.hpp>
#include <utils.hpp>
using namespace std;

// Return the nth node of a linked list
// if n is larger than list return last element
// ASSUME the nth node exists
ListNode *advance(ListNode *node, int n) {
    while (n-- and node->next) node = node->next;
    return node;
}
// Find A's predecessor, B's Successor, and the End of list2
// Perform the necessary assignments
// O(m+n) time, constant space
// Technically there's a memory leak of the removed elements, but we're not considering it
ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2) {
    auto aPred = advance(list1, a - 1); // Get A's Predecessor
    auto bSucc = advance(list1, b + 1); // Get B's Successor
    auto list2End = advance(list2, 100000); // Get the end of list2

    aPred->next = list2;
    list2End->next = bSucc;
    return list1;
}

bool checkResult(ListNode *head, vector<int> expected) {
    for (auto it = begin(expected); it != end(expected); it++) {
        if (!head) return false;
        if (head->val != *it) return false;
        head = head->next;
    }
    return true;
}

TEST_CASE("1669_example1", "[1669]") {
    auto l1 = {0, 1, 2, 3, 4, 5};
    auto a = 3;
    auto b = 4;
    auto l2 = {1000000, 1000001, 1000002};
    auto expected = {0, 1, 2, 1000000, 1000001, 1000002, 5};
    auto list1 = makeList(l1);
    auto list2 = makeList(l2);
    //    printList(list1);
    //    printList(list2);

    auto result = mergeInBetween(list1, a, b, list2);
    REQUIRE(checkResult(result, expected));
}