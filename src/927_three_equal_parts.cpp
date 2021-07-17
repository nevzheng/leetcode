//
// Created by Nevin Zheng on 7/17/21.
//

#include <algorithm>
#include <iostream>
#include <vector>

#include <catch2/catch.hpp>
using namespace std;

/**
 * We First note that a necessary condition for a valid partitioning is for there to be an equal number of ones in each partition.
 * Thus the total number of ones must be divisible by three.
 * First we count the number of ones, then check if its divisible by three. If its not we can return impossible {-1,-1}
 * If there are no Ones then the array is all zero so we can return any partition, say {0,N-1};
 * Let T = NumOnes/3
 * We then Locate the indices of the 1st 1, the Tth one, and the 2*Tth one. These indices are the START of our partitions
 * let p1=indexOf(1st One), p2=indexOf(2nd One), p3=indexOf(3rd One)
 * we then advance all the pointer through the array until p3 reaches the final element. We also check to ensure that all A[p1] == A[p2] == A[p3]
 * If there is a mismatch, that means that the arrays are unequal and partitioning is impossible.
 * @param A
 * @return
 */
vector<int> threeEqualParts(const vector<int> &A) {
    int N = A.size();
    auto oneCount = count(cbegin(A), cend(A), 1);// Count the number of ones in the array
    if (oneCount % 3 != 0) return {-1, -1};      // The partitioning must have and equal number of ones in each subsection.
    if (oneCount == 0) return {0, N - 1};
    auto T = oneCount / 3;// The number of ones in each section

    // Find the index of the first 1, the Tth 1, and the 2Tth 1. 0, T, and 2T index respectively
    int p1(-1), p2(-1), p3(-1), n1(0);
    for (int i = 0; i < N; i++) {
        if (A[i] == 1) {
            if (n1 == 0) p1 = i;
            if (n1 == T) p2 = i;
            if (n1 == 2 * T) p3 = i;
            n1++;
        }
    }
    // Check all elements before and after each part
    // Advance the partition from the start of the partition, to the end of the partition
    while (p3 < N - 1) {
        p1++;
        p2++;
        p3++;
        if (A[p1] != A[p2] or A[p2] != A[p3] or A[p1] != A[p3]) return {-1, -1};
    }
    return {p1, p2 + 1};
}


TEST_CASE("927ex1", "[927]") {
    vector<int> nums = {1, 0, 1, 0, 1};
    vector<int> expected = {0, 3};
    auto result = threeEqualParts(nums);
    REQUIRE(expected == result);
}


/* A Worked Example. Invalid
 * 1 0 0 0 1 0 1 0 1 0 0 0 0 1 0 1                     // 6 1s in array, 6/3 =2, 0, 2, 4
 * (1)  0   0  0 1 0 (1)  0   1  0 0 0 0 (1) 0    1    // OK
 *  1  (0)  0  0 1 0  1  (0)  1  0 0 0 0  1  (0)  1    // OK
 *  1   0  (0) 0 1 0  1   0  (1) 0 0 0 0  1   0   (1) // Advance, then detected a mismatch, so invalid; Stop
 * */
