// UnionFind.cpp
// Created by Nevin Zheng on 7/23/21.
//

//
// Created by Nevin Zheng on 7/23/21.
//

#include "UnionFind.hpp"

void union_find::UnionFind::unite(int p, int q) {
  auto p_root = find(p);
  auto q_root = find(q);
  if (p_root == q_root) return;
  if (size_[p_root] < size_[q_root]) {
    size_[q_root] += size_[p_root];
    id_[p_root] = q_root;
  } else {
    size_[p_root] += size_[q_root];
    id_[q_root] = p_root;
  }
}

bool union_find::UnionFind::connected(int p, int q) {
  return find(p) == find(q);
}

int union_find::UnionFind::size(int p) { return size_[find(p)]; }

int union_find::UnionFind::find(int p) {
  auto root = p;
  while (root != id_[root]) root = id_[root];
  while (p != root) {  // Do Path Compression
    auto next = id_[p];
    id_[p] = root;
    p = next;
  }
  return root;
}

union_find::UnionFind::UnionFind(int n)
    : id_(vector<int>(n)), size_(vector(n, 1)) {
  iota(begin(id_), end(id_), 0);
}
