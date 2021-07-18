//
// Created by Nevin Zheng on 7/16/21.
//
//
// Created by Nevin Zheng on 7/16/21.
//

#include <algorithm>
#include <unordered_map>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;

// Following from "1_two_sum", we can apply the same solution in O(n) time and O(n) memory
// However there is another interesting solution that we can apply now that the list is sorted.
// We iterate over the array. For each i, A[i] we can use binary search to search for the complement
// tgt - A[i] in the range A[i+1:]
// This is O(nlgn) time and O(1) space
vector<int> twoSumSortedBinarySearch(const vector<int> &A, int tgt) {
    for (auto it = begin(A); it != end(A); it++) {
        auto comp = tgt - *it;// Complement of it
        if (auto jt = lower_bound(it + 1, end(A), comp); jt != end(A) and *jt == comp) {
            int idx = (int) distance(begin(A), it) + 1;
            int jdx = (int) distance(begin(A), jt) + 1;
            return {idx, jdx};
        }
    }
    return {};
}
// This is an O(n) solution which is strictly better than Binary search
vector<int> twoSumSorted(const vector<int> &A, int tgt) {
    int N = A.size();
    int lo(0), hi(N - 1);
    while (lo < hi) {
        int sum = A[lo] + A[hi];
        if (sum == tgt) {
            return {lo + 1, hi + 1};
        } else if (sum > tgt) {
            hi--;
        } else {
            lo++;
        }
    }
    return {};
}

TEST_CASE("167_example1", "[167]") {
    auto nums = vector{2, 7, 11, 15};
    auto target = 9;
    auto expected = vector{1, 2};
    auto result = twoSumSorted(nums, target);
    REQUIRE(result == expected);
}

TEST_CASE("167_example2", "[167]") {
    auto nums = vector{2, 3, 4};
    auto target = 6;
    auto expected = vector{1, 3};
    auto result = twoSumSorted(nums, target);
    REQUIRE(result == expected);
}

TEST_CASE("167_example3", "[167]") {
    auto nums = vector{-1, 0};
    auto target = -1;
    auto expected = vector{1, 2};
    auto result = twoSumSorted(nums, target);
    REQUIRE(result == expected);
}
