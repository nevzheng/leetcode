//
// Created by Nevin Zheng on 7/13/21.
//
#pragma once
#include "Tree.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>

// Definition for a Singly Linked list
struct ListNode {
  int val{0};
  ListNode* next{nullptr};
  ListNode() = default;
  explicit ListNode(int x) : val(x) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
namespace utils {
template <typename T>
void printVector(const T& t) {
  std::copy(t.cbegin(), t.cend(),
            std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template <typename T>
void printVectorInVector(const T& t) {
  std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

ListNode* makeList(std::vector<int> a);
void printList(ListNode* head);
bool compareList(ListNode* a, ListNode* b);

/**
 * A Variadic Max Function
 * @tparam T1
 * @tparam T2
 * @tparam Tail
 * @param t1
 * @param t2
 * @param tail
 * @return
 */
template <typename T1, typename T2, typename... Tail>
constexpr auto max(T1&& t1, T2&& t2, Tail&&... tail) {
  if constexpr (sizeof...(tail) == 0) {
    return t1 > t2 ? t1 : t2;
  } else {
    return max(max(t1, t2), tail...);
  }
}

/**
 * A Variadic Min function
 * @tparam T1
 * @tparam T2
 * @tparam Tail
 * @param t1
 * @param t2
 * @param tail
 * @return
 */
template <typename T1, typename T2, typename... Tail>
constexpr auto min(T1&& t1, T2&& t2, Tail&&... tail) {
  if constexpr (sizeof...(tail) == 0) {
    return t1 < t2 ? t1 : t2;
  } else {
    return min(min(t1, t2), tail...);
  }
}
}  // namespace utils