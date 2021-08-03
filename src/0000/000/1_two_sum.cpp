//
// Created by Nevin Zheng on 7/16/21.
//

#include <catch2/catch.hpp>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

// We can solve this problem in O(N) time and O(N) memory with a single pass
// We first allocate a hash map with that maps from an element to its index
// As we iterate we will insert the element along with its index
// At each iteration we will check if the complement tgt - x has been previously
// inserted
vector<int> twoSum(const vector<int>& A, int tgt) {
  unordered_map<int, int> seen;  // Seen numbers
  int len = A.size();
  for (auto i = 0; i < len; i++) {
    if (auto it = seen.find(tgt - A[i]); it != end(seen)) {
      return {it->second, i};
    }
    seen.emplace(A[i], i);
  }
  return {};
}

TEST_CASE("1_example1", "[1]") {
  auto nums = vector{2, 7, 11, 15};
  auto target = 9;
  auto expected = vector{0, 1};
  auto result = twoSum(nums, target);
  REQUIRE(result == expected);
}

TEST_CASE("1_example2", "[1]") {
  auto nums = vector{3, 2, 4};
  auto target = 6;
  auto expected = vector{1, 2};
  auto result = twoSum(nums, target);
  REQUIRE(result == expected);
}

TEST_CASE("1_example3", "[1]") {
  auto nums = vector{3, 3};
  auto target = 6;
  auto expected = vector{0, 1};
  auto result = twoSum(nums, target);
  REQUIRE(result == expected);
}
