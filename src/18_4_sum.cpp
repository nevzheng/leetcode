//
// Created by Nevin Zheng on 7/16/21.
//
#include <set>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;

/**
 * One Way of solving the problem is to use four for loops and a set to filter our duplicates. That gives an answer in O(n^4) time, quartic. This is terrible.
 * That's the brute force approach.
 *
 * @param nums
 * @param tgt
 * @return
 */
vector<vector<int>> fourSumQuartic(vector<int> &A, int tgt) {
    auto N = A.size();
    set<vector<int>> res;

    //O(n^4)
    for (auto i = 0; i <= N - 4; i++) {
        for (auto j = i + 1; j <= N - 3; j++) {
            for (auto k = j + 1; k <= N - 2; k++) {
                for (auto l = k + 1; l <= N - 1; l++) {
                    if (A[i] + A[j] + A[k] + A[l] == tgt) {
                        // O(1), constant time to create sort and push a vector
                        // ASSUME pushing to set is O(1), its actually lg(n) n = size of set
                        vector v{A[i], A[j], A[k], A[l]};
                        sort(begin(v), end(v));
                        res.insert(v);
                    }
                }
            }
        }
    }
    // O(N) time to copy set to a result vector
    vector<vector<int>> ans;
    ans.reserve(res.size());
    std::move(begin(res), end(res), back_inserter(ans));
    return ans;
}

/**
 * In this solution we sort the array adopt the two sum solution to flatten two inner loops
 * This gives us O(n^3) complexity and O(N) memory to store the result.
 * @param A
 * @param tgt
 * @return
 */
vector<vector<int>> fourSum(vector<int> &A, int tgt) {
    auto N = A.size();
    if (N < 4) return {};
    sort(begin(A), end(A));// O(nlgn) , O(1);
    vector<vector<int>> res;
    for (auto i = 0; i < N; i++) {
        if (i > 0 and A[i - 1] == A[i]) continue;// Skip Duplicate Values of i
        for (auto j = i + 1; j < N; j++) {
            if (j > i + 1 and A[j - 1] == A[j]) continue;// Skip Duplicate Values of j
            // Break into the two sum pointer approach
            auto k = j + 1;
            auto l = N - 1;
            while (k < l) {
                if (auto sum = A[i] + A[j] + A[k] + A[l]; sum < tgt) {
                    k++;
                } else if (sum > tgt) {
                    l--;
                } else {
                    res.push_back({A[i], A[j], A[k], A[l]});
                    k++;
                    while (k < l and A[k - 1] == A[k]) k++;
                }
            }
        }
    }
    return res;
}


TEST_CASE("18ex1", "[18]") {
    vector<int> nums = {1, 0, -1, 0, -2, 2};
    auto tgt = 0;
    vector<vector<int>> expected = {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}};
    auto result = fourSum(nums, tgt);
    REQUIRE(result == expected);
}

TEST_CASE("18ex2", "[18]") {
    vector<int> nums = {2, 2, 2, 2, 2};
    auto tgt = 8;
    vector<vector<int>> expected = {{2, 2, 2, 2}};
    auto result = fourSum(nums, tgt);
    REQUIRE(result == expected);
}
