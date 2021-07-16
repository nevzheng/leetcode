//
// Created by Nevin Zheng on 7/12/21.
//

#include <catch2/catch.hpp>

#include <vector>
using namespace std;

// We can iterate from i=0..n, n=len(s)
// We will try to create assignments from s[i] to t[i]
// as well as from t[i] to s[i]
// If we find a violation of a previous mapping
// Otherwise we can return false
// O(n) time and O(1) space. It's ascii so theres an upperbound on space
bool isIsomorphic(string s, string t) {
    vector<int> s_t(256, -1), t_s(256, -1);

    for (auto i = 0; i < s.size(); i++) {
        auto [x, y] = std::tie(s[i], t[i]);
        // Case 1: No mapping in either map
        if (s_t[x] == -1 and t_s[y] == -1) {
            s_t[x] = y;
            t_s[y] = x;
        } else if (!(s_t[x] == y and t_s[y] == x)) {
            return false;
        }
    }
    return true;
}

TEST_CASE("test_205_example_1", "[205]") {
    REQUIRE(isIsomorphic("egg", "add") == true);
    REQUIRE(isIsomorphic("foo", "bar") == false);
    REQUIRE(isIsomorphic("paper", "title") == true);
    REQUIRE(isIsomorphic("badc", "baba") == false);
}