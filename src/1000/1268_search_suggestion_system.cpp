// 1268_search_suggestion_system
// Nevin Zheng
// 8/12/21

#include "../Trie.hpp"
#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * Building the trie take O(M) time where M is the total number of characters
 * Searching takes O(N) time where N is the len of the search word.
 * Building the trie takes the most time. but queries are fast.
 * The alternative solution is to do a binary search.
 */
class SolutionTrie {
 public:
  static vector<vector<string>> suggestedProducts(
      const vector<string>& products, const string& searchWord) {
    trie::Trie trie;
    for (const auto& w : products) trie.insert(w);
    vector<vector<string>> ans;
    vector<string> closest;
    string prefix;
    auto* cur = trie.get_root();
    for (auto c : searchWord) {
      prefix += c;
      closest.clear();
      cur = cur ? cur->get_child(c) : nullptr;
      if (cur) trie::Trie::find_words(cur, prefix, closest);
      ans.push_back(closest);
    }

    return ans;
  }
};

class Solution {
 public:
  static vector<vector<string>> suggestedProducts(vector<string>& products,
                                                  const string& searchWord) {
    std::sort(products.begin(), products.end());

    int bs_start = 0;
    int len = static_cast<int>(products.size());
    vector<vector<string>> ans;
    string prefix;
    for (auto c : searchWord) {
      prefix += c;
      auto start_it =
          std::lower_bound(products.begin() + bs_start, products.end(), prefix);
      auto start = static_cast<int>(std::distance(products.begin(), start_it));
      ans.emplace_back();  // push empty onto end
      for (auto i = start; i < min(start + 3, len); ++i) {
        if (products[i].compare(0, prefix.size(), prefix)) break;
        ans.back().push_back(products[i]);
      }
      bs_start = start;
    }
    return ans;
  }
};

TEST_CASE("1268::1", "[1268]") {
  vector<string> products{"mobile", "mouse", "moneypot", "monitor", "mousepad"};
  const string search_word = "mouse";
  const vector<vector<string>> expected{{"mobile", "moneypot", "monitor"},
                                        {"mobile", "moneypot", "monitor"},
                                        {"mouse", "mousepad"},
                                        {"mouse", "mousepad"},
                                        {"mouse", "mousepad"}};
  REQUIRE(Solution().suggestedProducts(products, search_word) == expected);
}

TEST_CASE("1268::2", "[1268]") {
  vector<string> products{"havana"};
  const string search_word = "havana";
  const vector<vector<string>> expected{{"havana"}, {"havana"}, {"havana"},
                                        {"havana"}, {"havana"}, {"havana"}};
  REQUIRE(Solution().suggestedProducts(products, search_word) == expected);
}

TEST_CASE("1268::3", "[1268]") {
  vector<string> products{"bags", "baggage", "banner", "box", "cloths"};
  const string search_word = "bags";
  const vector<vector<string>> expected{{"baggage", "bags", "banner"},
                                        {"baggage", "bags", "banner"},
                                        {"baggage", "bags"},
                                        {"bags"}};
  REQUIRE(Solution().suggestedProducts(products, search_word) == expected);
}

TEST_CASE("1268::4", "[1268]") {
  vector<string> products{"havana"};
  const string search_word = "tatiana";
  const vector<vector<string>> expected{{}, {}, {}, {}, {}, {}, {}};
  REQUIRE(Solution().suggestedProducts(products, search_word) == expected);
}