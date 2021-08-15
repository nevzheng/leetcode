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
  Node* next{nullptr};
  Node* random{nullptr};

  explicit Node(int _val) : val(_val) {}
};
class Solution {
 public:
  /**
   * This Solution uses a hash map to record a mapping between the pointers of
   * the original to the copy. The copy is made with random ptrs pointing back
   * to the original list. Once all nodes have been copied another traversal is
   * done to fix up the random ptrs using the created map O(N) time and O(N)
   * memory. 1 Traversal of original list and 2 traversals of the copya
   * @param head
   * @return
   */
  static Node* copyRandomListHashMap(Node* head) {
    Node* cur{head};
    Node* new_head{nullptr};
    Node* new_cur{nullptr};
    map<Node*, Node*> copied;
    while (cur) {
      auto* cpy = new Node(cur->val);
      cpy->random = cur->random;
      copied[cur] = cpy;
      cur = cur->next;
      if (!new_head) {
        new_head = cpy;
        new_cur = cpy;
      } else {
        new_cur->next = cpy;
        new_cur = new_cur->next;
      }
    }
    new_cur = new_head;
    while (new_cur) {
      if (new_cur->random) new_cur->random = copied[new_cur->random];
      new_cur = new_cur->next;
    }
    return new_head;
  }

  /**
   * This Solution is pretty clever. It copies the nodes of the old list,
   * splicing the new nodes after the originals. After the original copy pass,
   * it does and additional two passes to i. fix up the pointers, ii. Splice out
   * the new list In an interview its worth mentioning both solutions, but the
   * above method is safer and clearer. O(N) time. Three passes, O(1) time, no
   * additional memory for recording mapping between old and new pointers
   * @param head
   * @return
   */
  static Node* copyRandomListSplicing(Node* head) {
    if (!head) return nullptr;
    Node* cur{head};
    Node* new_cur{nullptr};
    Node* new_head{nullptr};
    // Make a Copy of the Original List Splicing copies after the originals
    while (cur) {
      auto* tmp = cur->next;
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
    cur = head, new_head = head->next, new_cur = head->next;
    while (cur && new_cur) {
      cur->next = cur->next ? cur->next->next : cur->next;
      new_cur->next = new_cur->next ? new_cur->next->next : new_cur->next;
      cur = cur->next;
      new_cur = new_cur->next;
    }
    return new_head;
  }
};

TEST_CASE("138ex1", "[138]") {
  //    Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
  //    Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
  auto seven = make_unique<Node>(7);
  auto thirteen = make_unique<Node>(13);
  auto eleven = make_unique<Node>(11);
  auto ten = make_unique<Node>(10);
  auto one = make_unique<Node>(1);

  seven->next = thirteen.get();

  thirteen->next = eleven.get();
  thirteen->random = seven.get();

  eleven->next = ten.get();
  eleven->random = one.get();

  ten->next = one.get();
  ten->random = eleven.get();

  one->random = seven.get();

  auto* result = Solution::copyRandomListHashMap(seven.get());

  // Verifying is a little tricky, just use leetcode
  REQUIRE(result != nullptr);
}

TEST_CASE("138ex2", "[138]") {
  //    Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
  //    Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
  auto seven = make_unique<Node>(7);
  auto thirteen = make_unique<Node>(13);
  auto eleven = make_unique<Node>(11);
  auto ten = make_unique<Node>(10);
  auto one = make_unique<Node>(1);

  seven->next = thirteen.get();

  thirteen->next = eleven.get();
  thirteen->random = seven.get();

  eleven->next = ten.get();
  eleven->random = one.get();

  ten->next = one.get();
  ten->random = eleven.get();

  one->random = seven.get();

  auto* result = Solution::copyRandomListSplicing(seven.get());

  // Verifying is a little tricky, just use leetcode
  REQUIRE(result != nullptr);
}