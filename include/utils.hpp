//
// Created by Nevin Zheng on 7/13/21.
//
#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Definition for a Singly Linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
namespace utils {

    template<typename T>
    void printVector(const T &t) {
        std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
    }

    template<typename T>
    void printVectorInVector(const T &t) {
        std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
    }
}// namespace utils
ListNode *makeList(std::vector<int> a);
void printList(ListNode *head);
bool compareList(ListNode *a, ListNode *b);