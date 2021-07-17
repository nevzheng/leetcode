//
// Created by Nevin Zheng on 7/16/21.
//
#include <algorithm>
#include <numeric>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;
/**
 * Observation all values of the firstPositive are in the range [1, n+1];
 * Case1: All values from 1 to N are present => answer is N+1
 * Case2: All values are greater than N => answer is 1
 * Case3: All Values are in between 1 and n, => answer is some value in 1, n+1
 * If you try a bunch of arrays you'll see that its not possible to get the answer outside of 1, n+1
 *
 * That means we can find the answer in O(n) time and memory. Its O(1) if we are able to reuse the array
 *
 * To reuse the array we're going to use the sign bit to indicate whether or not a value is present in the array. Negative means we've see the value
 * We will make a first pass switching out of bound values to 1. We will also record the presence/absence of the value 1. If we don't see it we can return 1 as the answer
 * Our next pass will set the sign bits on each index. we have to adjust the index because positve numbers go from 1-n+1 while our indices are 0 indexed from 0, n
 * Our third pass will look for a positive number. the sign bit indicates that we haven't seen the value. So we can return i+1 as our answer;
 * If all the nums are positive we can return N+1 as our answer.
 * @param A
 * @return
 */
int firstMissingPositive(vector<int> &A) {
    auto N = A.size();
    auto hasOne = false;
    for (auto i = 0; i < N; i++) {
        if (A[i] == 1) hasOne = true;
        if (A[i] <= 0 or A[i] > N) A[i] = 1;
    }
    if (!hasOne) return 1;

    for (auto i = 0; i < N; i++) {
        auto idx = abs(A[i]) - 1;
        A[idx] = -abs(A[idx]);
    }

    for (auto i = 0; i < N; i++) {
        if (A[i] > 0) return i + 1;
    }
    return N + 1;
}

TEST_CASE("41ex1", "[41]") {
    vector<int> nums = {1, 2, 0};
    auto expected = 3;
    REQUIRE(firstMissingPositive(nums) == expected);
}

TEST_CASE("41ex2", "[41]") {
    vector<int> nums = {7, 8, 9, 11, 12};
    auto expected = 1;
    REQUIRE(firstMissingPositive(nums) == expected);
}