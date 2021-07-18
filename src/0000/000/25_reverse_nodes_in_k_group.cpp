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

/**
 * We will solve this problem in a recursive fashion. You really need to draw this out on a whiteboard
 * At each stack fram we'll have head, p, q, and r ptrs
 * Carefully trace the code with paper and a diagram to understand
 * @param head
 * @param k
 * @return
 */
ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *p = head, *q(nullptr), *r(nullptr);
    auto size = countNodes(head);// O(N) Call Per segment. Can refactor to pass as arg
    auto i(0);
    while (p and i < k) {// Reversing the linked list
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

TEST_CASE("25ex1", "[25]") {
    vector<int> input = {1, 2, 3, 4, 5};
    auto k = 3;
    vector<int> expected = {3, 2, 1, 4, 5};

    auto inputList = makeList(input);
    auto expectedList = makeList(expected);
    auto resultList = reverseKGroup(inputList, k);

    REQUIRE(compareList(resultList, expectedList));
}
