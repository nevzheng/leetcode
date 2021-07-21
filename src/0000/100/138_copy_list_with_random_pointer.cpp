// 138_copy_list_with_random_pointer.cpp
// Nevin Zheng
// 7/21/21

#include <bits/stdc++.h>

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node *next;
    Node *random;

    explicit Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

/**
 * This Solution uses a hash map to record a mapping between the pointers of the original to the copy.
 * The copy is made with random ptrs pointing back to the original list.
 * Once all nodes have been copied another traversal is done to fix up the random ptrs using the created map
 * O(N) time and O(N) memory. 1 Traversal of original list and 2 traversals of the copya
 * @param head
 * @return
 */
Node *copyRandomListHashMap(Node *head) {
    Node *cur{head}, *newCur{nullptr}, *newHead{nullptr};
    map<Node *, Node *> copied;
    while (cur) {
        auto cpy = new Node(cur->val);
        cpy->random = cur->random;
        copied[cur] = cpy;
        cur = cur->next;
        if (!newHead) {
            newHead = cpy;
            newCur = cpy;
        } else {
            newCur->next = cpy;
            newCur = newCur->next;
        }
    }
    newCur = newHead;
    while (newCur) {
        if (newCur->random) newCur->random = copied[newCur->random];
        newCur = newCur->next;
    }
    return newHead;
}

/**
 * This Solution is pretty clever. It copies the nodes of the old list, splicing the new nodes after the originals.
 * After the original copy pass, it does and additional two passes to i. fix up the pointers, ii. Splice out the new list
 * In an interview its worth mentioning both solutions, but the above method is safer and clearer.
 * O(N) time. Three passes, O(1) time, no additional memory for recording mapping between old and new pointers
 * @param head
 * @return
 */
Node *copyRandomListSplicing(Node *head) {
    if (!head) return nullptr;
    Node *cur{head}, *newHead{nullptr}, *newCur{nullptr};
    // Make a Copy of the Original List Splicing copies after the originals
    while (cur) {
        auto tmp = cur->next;
        cur->next = new Node(cur->val);
        cur->next->next = tmp;
        cur = tmp;
    }
    cur = head;
    // Adjust the random ptrs of the newly added nodes
    while (cur) {
        // If we see a spliced cpy
        if (cur->next) {
            if (cur->random) cur->next->random = cur->random->next;
        }
        // Skip to the next original Node,
        cur = cur->next ? cur->next->next : cur->next;
    }
    // Splice out the original list
    cur = head, newHead = head->next, newCur = head->next;
    while (cur && newCur) {
        cur->next = cur->next ? cur->next->next : cur->next;
        newCur->next = newCur->next ? newCur->next->next : newCur->next;
        cur = cur->next;
        newCur = newCur->next;
    }
    return newHead;
}

TEST_CASE("138ex1", "[138]") {
    //    Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
    //    Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
    auto seven = new Node(7);
    auto thirteen = new Node(13);
    auto eleven = new Node(11);
    auto ten = new Node(10);
    auto one = new Node(1);

    seven->next = thirteen;

    thirteen->next = eleven;
    thirteen->random = seven;

    eleven->next = ten;
    eleven->random = one;

    ten->next = one;
    ten->random = eleven;

    one->random = seven;

    auto result = copyRandomListHashMap(seven);

    // Verifying is a little tricky, just use leetcode
    REQUIRE(result != nullptr);
}


TEST_CASE("138ex2", "[138]") {
    //    Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
    //    Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
    auto seven = new Node(7);
    auto thirteen = new Node(13);
    auto eleven = new Node(11);
    auto ten = new Node(10);
    auto one = new Node(1);

    seven->next = thirteen;

    thirteen->next = eleven;
    thirteen->random = seven;

    eleven->next = ten;
    eleven->random = one;

    ten->next = one;
    ten->random = eleven;

    one->random = seven;

    auto result = copyRandomListSplicing(seven);

    // Verifying is a little tricky, just use leetcode
    REQUIRE(result != nullptr);
}