// 915_partition_array_into_disjoint_intervals
// Nevin Zheng
// 7/22/21

#include <bits/stdc++.h>

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

///**
// * In this solution we will attempt to brute force the answer.
// * We will test possible partitioning of the array into left and right intervals
// * For each partition we will see if the MAX of the left partition is less than or equal to the MIN of the right partition
// * This approach will take O(n^2) time and O(1) memory
// *
// * @param A
// * @return
// */
//int partitionDisjoint(const vector<int> &A) {
//    for (auto it = cbegin(A); it != cend(A); ++it) {
//        // Is MAX(A[0..i]) <= MIN(A[i+1..N-1])?
//        auto maxL = *max_element(begin(A), it);
//        auto minR = *min_element(it + 1, end(A));
////        fmt::print("([{}, {}], {}) , ([{}, {}], {})\n",
////                   0, distance(cbegin(A), it), maxL,
////                   distance(begin(A), it + 1), A.size() - 1, minR);
//        if (maxL <= minR) return (int) distance(begin(A), it) + 1;
//    }
//    return -1;// unreachable
//}

/**
 * Now that we understand what the problem is asking for we can develop a more optimal solution
 * The O(n^2) algorithm is correct but TLE when scored so we'll have to develop something more optimal.
 * We'll use inclusive_scans to find the min of possible left partitions and the maxes of possible right partitions
 * This will give us O(n) time and memory.
 * @param A
 * @return
 */
int partitionDisjoint(const vector<int> &A) {
    auto N = A.size();
    vector<int> maxLeft(N), minRight(N);
    inclusive_scan(cbegin(A), cend(A), begin(maxLeft), [](const auto a, const auto b) { return max(a, b); });
    inclusive_scan(crbegin(A), crend(A), rbegin(minRight), [](const auto a, const auto b) { return min(a, b); });
    for (auto i = 0ul; i < N; i++) {
        if (maxLeft[i] <= minRight[i + 1]) return (int) (i + 1);
    }
    return -1;// unreachable
}

TEST_CASE("915ex1", "[915]") {
    vector<int> input = {5, 0, 3, 8, 6};
    auto expected = 3;
    REQUIRE(partitionDisjoint(input) == expected);
}

TEST_CASE("915ex2", "[915]") {
    vector<int> input = {1, 1, 1, 0, 6, 12};
    auto expected = 4;
    REQUIRE(partitionDisjoint(input) == expected);
}