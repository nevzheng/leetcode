#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  int maxArea(vector<int>& H) {
    int l = 0;
    int r = size(H) - 1;
    int mx = -1;
    while (l < r) {
      auto h = std::min(H[l], H[r]);
      auto w = r - l;
      auto a = h * w;
      mx = std::max(mx, a);
      if (H[l] <= H[r]) {
        ++l;
      } else {
        --r;
      }
    }
    return mx;
  }
};