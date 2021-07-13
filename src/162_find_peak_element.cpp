//
// Created by Nevin Zheng on 7/13/21.
//
#include <catch2/catch.hpp>

#include <vector>
using namespace std;

// The array is either strictly increasing or decreasing or some combination of the two
// We just need to look for an inversion point whene it switches from increasing to decreasing
// A[i] > A[i+1]
// We'll stop at A[n-2]
// If we reach i-2 we can return the last element
// This takes O(n) time and O(1) memory
int findPeakElement(vector<int> &A) {
    auto n = A.size();
    for(auto i=0; i < A.size()-1; i++){
        if (A[i] > A[i+1] ){
            return i;
        }
    }
    return (int) n-1 ;
}

// We can view the array as an alternating sequence of increasing and decreasing segments
// We can perform a binary search for the index where the array inverts, switches from increasing to decreasing or vice versa
int findPeakElement(const vector<int> &A) {
    int lo(0);
    int hi((int)A.size() - 1);
    while (lo < hi) {
        auto mi = lo + ((hi - lo) / 2);
        if (A[mi] > A[mi + 1]) {
            hi = mi;
        } else {
            lo = mi + 1;
        }
    }
    return lo;
}

// The Array can be divided into increasing and decreasing cases
// We note that adjacent elements are not equal
// thus we can linearly search a point where A[i] > A[i+1], where an increasing sequence starts decreasing
// because the arrays are sorted, we can then apply a binary search
// our predicate is A[mid] > A[mi+1], OR If our mid point is greater than the next element, i.e. the inversion hasn't happened

TEST_CASE("test_162_example_1") {
    vector<int> v = {1, 2, 1, 3, 5, 6, 4};
    int peakElement = findPeakElement(v);
    bool result = peakElement == 1 || peakElement == 5;
    REQUIRE(result);
}

TEST_CASE("test_162_example_2") {
    vector<int> v = {1, 2, 3, 1};
    int peakElement = findPeakElement(v);
    bool result = peakElement == 2;
    REQUIRE(result);
}