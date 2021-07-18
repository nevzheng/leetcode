//
// Created by Nevin Zheng on 7/16/21.
//

#include <algorithm>
#include <unordered_map>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;

// We can solve this problem in O(N) time and O(N) memory with a single pass
// We first allocate a hash map with that maps from an element to its index
// As we iterate we will insert the element along with its index
// At each iteration we will check if the complement tgt - x has been previously inserted
vector<int> twoSum(const vector<int> &A, int tgt) {
    unordered_map<int, int> S;// Seen numbers
    S.reserve(A.size());      // Preallocate N elements
    for (auto i = 0; i < A.size(); i++) {
        if (auto it = S.find(tgt - A[i]); it != end(S)) {
            return {it->second, i};
        } else {
            S.emplace(A[i], i);
        }
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
