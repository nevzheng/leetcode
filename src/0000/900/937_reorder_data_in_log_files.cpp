// 937_reorder_data_in_log_files
// Nevin Zheng
// 8/13/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static vector<string> reorderLogFiles(vector<string>& logs) {
    deque<string> ans;
    int count = 0;
    for (const auto& log : logs) {
      if (islower(log.back())) {
        ans.push_front(log);
        ++count;
      } else {
        ans.push_back(log);  // Push Digits to back
      }
    }
    auto cmp = [](const auto& x, const auto& y) {
      auto xs = string_view(x).substr(x.find(' '));
      auto ys = string_view(y).substr(y.find(' '));
      return xs == ys ? x < y : xs < ys;
    };
    std::sort(ans.begin(), ans.begin() + count, cmp);
    return vector(ans.begin(), ans.end());
  }
};

TEST_CASE("937::1", "[937]") {
  vector<string> logs{"dig1 8 1 5 1", "let1 art can", "dig2 3 6",
                      "let2 own kit dig", "let3 art zero"};
  vector<string> expected{"let1 art can", "let3 art zero", "let2 own kit dig",
                          "dig1 8 1 5 1", "dig2 3 6"};
  REQUIRE(Solution::reorderLogFiles(logs) == expected);
}
