//
// Created by Nevin Zheng on 7/12/21.
//

#include <catch2/catch.hpp>

#include <unordered_map>
#include <vector>
using namespace std;

vector<int> topKFrequent(vector<int> &nums, int k) {
    int n = nums.size();
    // Use an Unordered Map to count Frequencies
    unordered_map<int, int> m;
    for (const auto x : nums) {
        m[x] += 1;
    }
    // Convert the Map into an Array
    vector<int> v;
    v.reserve(m.size());
    std::transform(begin(m), end(m), back_inserter(v), [](const auto &x) { return x.first; });
    // do a quick select
    nth_element(rbegin(v), rbegin(v) + k, rend(v),
                [&](const auto &a, const auto &b) {
                    return m[a] > m[b];
                });
    return vector(rbegin(v), rbegin(v) + k);
}

TEST_CASE("test_347_example_1", "[347]") {
    vector<int> v = {1, 1, 1, 2, 2, 3};
    vector<int> r = {1, 2};
    REQUIRE(topKFrequent(v, 2) == r);
}