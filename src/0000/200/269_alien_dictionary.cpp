// 269_alien_dictionary
// Leetcode premium but it's here:
// https://zhuhan0.blogspot.com/2017/06/leetcode-269-alien-dictionary.html
// Nevin Zheng 7/22/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * Let's imagine that each word is a directed graph that gives us information
 * about how the letters are supposed to be ordered Adjacent letters indicate a
 * dependency Each additional word can give us more information about the proper
 * order of the graph. We should build a single connected graph based on the
 * orderings of letters in each word. My approach is to find a valid topological
 * ordering Topological orderings are not necessarily unique, but it should work
 * if we have enough words and constraints in the input. There are two
 * algorithms that we can use. One is Khan's algorithm and the other is a DFS
 * based algorithm. They both run in O(E+V) time. and O(V) memory. V is the
 * number of unique letters, and E is dependent on the relationship in the
 * graph. Lets just assume its V^2, which comes from an assumption of a fully
 * connected graph. This is too conservative since we have a DAG which can't be
 * fully connected.
 * @return
 */
string alienOrder(const vector<string>& words) {
  const auto alphabet_len = 26;
  vector<int> in_degree(alphabet_len, -1);
  vector<set<int>> graph(
      alphabet_len,
      set<int>());  // An Adjacency list representation of the graph
  queue<int> zero_degree;
  vector<int> top_sort;
  string ans;
  auto n = words.size();
  // Compare adjacent words
  for (auto w = 0UL; w <= n - 2; w++) {
    auto w1 = words[w];
    auto w2 = words[w + 1];
    // Be Sure to iterate over the smaller length string
    auto min_len = min(w1.size(), w2.size());
    for (auto i = 0UL; i < min_len; i++) {
      auto u_id = w1[i] - 'a';
      auto v_id = w2[i] - 'a';
      // Indicate these vertices exist
      if (in_degree[u_id] < 0) in_degree[u_id] = 0;
      if (in_degree[v_id] < 0) in_degree[v_id] = 0;
      if (w1[i] == w2[i]) continue;  // Avoid Self Edges
      if (!graph[u_id].count(v_id)) {
        // Add an Edge from uId -> vId
        graph[u_id].insert(v_id);
        in_degree[v_id]++;
      }
    }
  }
  for (auto i = 0; i < static_cast<int>(in_degree.size()); i++) {
    if (in_degree[i] == 0) {
      fmt::print("Pushing to zero degree: {}\n", static_cast<char>(i + 'a'));
      zero_degree.push(i);
    }
  }
  while (!zero_degree.empty()) {
    auto u = zero_degree.front();
    zero_degree.pop();
    fmt::print("top_sort: examining: {}\n", static_cast<char>(u + 'a'));
    top_sort.push_back(u);
    for (auto v : graph[u]) {  // Erase Edges and decrease inDegree of v
      //      graph[u].erase(v);       // Not Strictly Necessary. Need to move
      //      to another loop
      fmt::print("removing {} -> {}\n", static_cast<char>(u + 'a'),
                 static_cast<char>(v + 'a'));
      in_degree[v]--;
      if (in_degree[v] == 0) {
        fmt::print("Added to zero_degree: {}", static_cast<char>(v + 'a'));
        zero_degree.push(v);
      }
    }
  }
  ans.resize(top_sort.size());
  transform(begin(top_sort), end(top_sort), begin(ans),
            [](const auto x) { return static_cast<char>(x + 'a'); });
  return ans;
}

TEST_CASE("269ex1", "[269]") {
  vector<string> input = {"wrt", "wrf", "er", "ett", "rftt"};
  string expected = "wertf";
  REQUIRE(alienOrder(input) == expected);
}

TEST_CASE("269ex2", "[269]") {
  vector<string> input = {"z", "x"};
  string expected = "zx";
  REQUIRE(alienOrder(input) == expected);
}

TEST_CASE("269ex3", "[269]") {
  vector<string> input = {"z", "x", "z"};
  string expected;
  REQUIRE(alienOrder(input) == expected);
}