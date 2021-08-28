// 331_verify_preorder_serialization_binary_tree
// Nevin Zheng
// 8/26/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static bool isValidSerialization(const string& preorder) {
    stringstream ss(preorder);
    string cur;
    auto nodes = 1;
    while (std::getline(ss, cur, ',')) {
      nodes--;
      if (nodes < 0) return false;
      if (cur != "#") nodes += 2;
    }
    return nodes == 0;  // All Tokens Processes Successfully
  }
};

TEST_CASE("331::1", "[331]") {
  auto preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"s;
  auto expected = true;
  REQUIRE(Solution::isValidSerialization(preorder) == expected);
}

TEST_CASE("331::2", "[331]") {
  auto preorder = "1,#"s;
  auto expected = false;
  REQUIRE(Solution::isValidSerialization(preorder) == expected);
}

TEST_CASE("331::3", "[331]") {
  auto preorder = "9,#,#,1"s;
  auto expected = false;
  REQUIRE(Solution::isValidSerialization(preorder) == expected);
}

TEST_CASE("331::4", "[331]") {
  auto preorder = "#"s;
  auto expected = true;
  REQUIRE(Solution::isValidSerialization(preorder) == expected);
}

TEST_CASE("331::5", "[331]") {
  auto preorder = "#,#,#"s;
  auto expected = false;
  REQUIRE(Solution::isValidSerialization(preorder) == expected);
}

TEST_CASE("331::6", "[331]") {
  auto preorder = "9,#,93,#,9,9,#,#,#"s;
  auto expected = true;
  REQUIRE(Solution::isValidSerialization(preorder) == expected);
}
