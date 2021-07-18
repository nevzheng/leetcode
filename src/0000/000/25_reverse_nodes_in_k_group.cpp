//
// Created by Nevin Zheng on 7/18/21.
//
#include <vector>

#include <catch2/catch.hpp>
#include <utils.hpp>

using namespace std;

int countNodes(ListNode *head) {
    auto count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *p = head, *q = nullptr, *r = nullptr;
    auto size = countNodes(head);
    auto currLen(0), i(0);

    // Reversing the linked list
    while (p and i < k) {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
        currLen++;
        i++;
    }

    if (p and size - currLen >= k) {
        head->next = reverseKGroup(p, k);
    } else {
        head->next = p;
    }
    return q;
}

TEST_CASE("25ex1", "[25]") {
    vector<int> input = {1, 2, 3, 4, 5};
    auto k = 3;
    vector<int> expected = {3, 2, 1, 4, 5};

    auto inputList = makeList(input);
    auto expectedList = makeList(expected);
    auto resultList = reverseKGroup(inputList, k);

    REQUIRE(compareList(resultList, expectedList));
}
