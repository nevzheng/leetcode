// 216_combination_sum_3
// Nevin Zheng
// 7/18/21

#include <set>

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>

using namespace std;

template<typename T>
using Vec2 = vector<vector<T>>;
template<typename T>
using VSet = set<vector<T>>;

void cs3(const int k, VSet<int> &S, vector<int> curr, int len, int tgt, int digit) {
    if (len == k and tgt == 0) {// Just Right. Accept result from previous call
        sort(begin(curr), end(curr));
        S.insert(curr);
        return;
    }
    if (digit > 9 or len > k or tgt < 0) return;// Too Far, Stop Processing invalid call
    curr.push_back(digit);
    cs3(k, S, curr, len + 1, tgt - digit, digit + 1);// Include Digit
    curr.pop_back();
    cs3(k, S, curr, len, tgt, digit + 1);// Exclude Digit
}

Vec2<int> combinationSum3(int k, int tgt) {
    VSet<int> S;
    cs3(k, S, {}, 0, tgt, 1);
    Vec2<int> ans;
    move(begin(S), end(S), back_inserter(ans));
    return ans;
}

TEST_CASE("216ex1", "[216]") {
    auto k = 3, n = 7;
    Vec2<int> expected = {{1, 2, 4}};
    REQUIRE(combinationSum3(k, n) == expected);
}

TEST_CASE("216ex2", "[216]") {
    auto k = 9, n = 45;
    Vec2<int> expected = {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    REQUIRE(combinationSum3(k, n) == expected);
}