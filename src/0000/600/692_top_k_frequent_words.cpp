// 692_top_k_frequent_words
// AMZN OA 1
// Nevin Zheng
// 8/5/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  static vector<string> topKFrequent(const vector<string>& words, int k) {
    // Create a Map counting frequencies of each word, O(n) time/space
    map<string, int> freq;
    for (const auto& w : words) ++freq[w];

    // We want to find the top k most frequent elements
    // Create a min priority queue that uses freq as keys and
    // breaks ties using greater lexicographical order
    auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
      if (a.second != b.second) return a.second > b.second;
      return a.first < b.first;
    };
    std::priority_queue<pair<string, int>, vector<pair<string, int>>,
                        decltype(cmp)>
        pq(cmp);
    // Iterate through the frequencies
    // Push if less than k
    // If equal to k, only pop and insert if the new element is less than top
    // O(N lg k)time, O(k) space
    for (auto& it : freq) {
      if (static_cast<int>(pq.size()) < k) {
        pq.push(it);
      } else if (cmp(it, pq.top())) {
        pq.pop();
        pq.push(it);
      }
    }
    // Dequeue the results O(k time), O(k) space
    vector<string> ans;
    ans.reserve(k);
    while (!pq.empty()) {
      ans.push_back(pq.top().first);
      pq.pop();
    }
    std::reverse(ans.begin(), ans.end());  // O(k) time;
    return ans;
  }
};

TEST_CASE("692ex1", "[692]") {
  const vector<string> words = {"i", "love", "leetcode", "i", "love", "coding"};
  const auto k = 2;
  const vector<string> expected = {"i", "love"};
  REQUIRE(Solution::topKFrequent(words, k) == expected);
}

TEST_CASE("692ex2", "[692]") {
  const vector<string> words = {"the", "day", "is",    "sunny", "the",
                                "the", "the", "sunny", "is",    "is"};
  const auto k = 4;
  const vector<string> expected = {"the", "is", "sunny", "day"};
  REQUIRE(Solution::topKFrequent(words, k) == expected);
}