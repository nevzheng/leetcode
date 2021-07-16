//
// Created by Nevin Zheng on 7/15/21.
//
#include <algorithm>
#include <catch2/catch.hpp>
#include <iostream>
#include <utils.hpp>
#include <vector>

using namespace std;
//
//int triangleNumber(vector<int> A) {
//    auto n = A.size();
//    if (n < 3) return 0;
//    auto count = 0;
//
//    sort(begin(A), end(A));// O(n lgn) time
//
//    for (auto i = 0; i < n - 2; i++) {
//        for (auto j = i + 1; j < n - 1 && A[i] != 0; j++) {
//            auto k = lower_bound(begin(A), end(A), A[i] + A[j]) - begin(A);
//            count += k - j - 1;
//        }
//    }
//    return count;
//}
// We can apply binary search to optimize the solution
// First we sort in ascending order in O(n lgn) time
// We then iterate over indices i and j, st i <= j and a[i] <= a[j] because its sorted
// We then can binary search for a[i] + a[j] in the array for candidates for the third side
// we will increment count by the number of elements between k and j , less 1, as the sum must be greater.
int triangleNumber(vector<int> A) {
    auto n = A.size();
    if (n < 3) return 0;
    sort(begin(A), end(A));// T= n lg n
    auto count = 0;
    for (auto i = 0; i < n - 2; i++) {
        if (A[i] == 0) continue;// Skip any zero elements
        for (auto j = i + 1; j < n - 1; j++) {
            int k = lower_bound(begin(A), end(A), A[i] + A[j]) - begin(A);
            count += k - j - 1;
        }
    }
    return count;
}


TEST_CASE("611_example1", "[611]") {
    vector<int> nums = {2, 2, 3, 4};
    auto count = 3;
    REQUIRE(triangleNumber(nums) == count);
}

TEST_CASE("611_example2", "[611]") {
    vector<int> nums = {1};
    auto count = 0;
    REQUIRE(triangleNumber(nums) == count);
}