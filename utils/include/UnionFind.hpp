//
// Created by Nevin Zheng on 7/23/21.
//
#pragma once

#include <numeric>
#include <vector>

class UnionFind {
 private:
  /**
   * Vector containing the parent nodes of a vertex
   * Root Nodes have self loops
   * Example:
   * id_[p] = p => Root Component which uniquely identifies component
   * id_[p] = q => p belongs to same component as q.
   */
  std::vector<int> id_;
  std::vector<int> size_;

 public:
  /**
   * Construct a new UnionFind data structure with n components
   * @param n
   */
  explicit UnionFind(int n);

  /**
   * Determine which component p belongs to
   * @param p
   * @return index of the set that p belongs to
   */
  int find(int p);

  /**
   * Determine if p and q belong to the same component
   * @param p
   * @param q
   * @return true if same component, else false
   */
  bool connected(int p, int q);

  /**
   * Return the size of the component that p belongs to
   * @param p
   * @return
   */
  int size(int p);

  /**
   * Perform a union operation between Component p and Component q
   * Uses "Union By Size" to limit tree depth
   * @param p
   * @param q
   */
  void unite(int p, int q);
};