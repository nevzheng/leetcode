// 1436_destination_city
// Nevin Zheng
// 9/4/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  string destCity(const vector<vector<string>>& paths) {
    std::map<string, int> out_degree;
    for (const auto& p : paths) {
      ++out_degree[p[0]];  // Increment out degree for u
      out_degree[p[1]];    // touch out_degree[v] to make sure it exists
    }
    for (const auto& [k, v] : out_degree)
      if (v == 0) return k;
    return "";
  }
};