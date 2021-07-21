// 133_clone_graph
// Nevin Zheng
// 7/21/21

#include <bits/stdc++.h>

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node *> neighbors;
    Node() : val(0), neighbors({}) {}
    explicit Node(int _val) : val(_val), neighbors({}) {}
    explicit Node(int _val, const vector<Node *> &&_neighbors) : val(_val), neighbors(_neighbors) {}
};

void clone(vector<Node *> &copied, map<Node *, Node *> &mapping, set<Node *> &visited, Node *u) {
    if (visited.count(u)) return;
    visited.insert(u);// Mark as visited
    auto cpy = new Node(u->val);
    cpy->neighbors = u->neighbors;// Naively copy the original neighbors
    copied.push_back(cpy);        // Save the copy to copied
    mapping[u] = cpy;             // Set a mapping
    for (auto v : u->neighbors) clone(copied, mapping, visited, v);
}

Node *cloneGraph(Node *node) {
    if (!node) return nullptr;
    vector<Node *> copied;
    map<Node *, Node *> mapping;
    set<Node *> visited;
    // DFS the graph making copies of the nodes
    clone(copied, mapping, visited, node);
    // Transform the neighbors of each node
    for (auto u : copied) {
        transform(begin(u->neighbors),
                  end(u->neighbors),
                  begin(u->neighbors),
                  [&mapping](const auto v) { return mapping[v]; });
    }
    return copied.front();
}


TEST_CASE("133ex1", "[133]") {
    auto one = new Node(1);
    auto two = new Node(2);
    auto three = new Node(3);
    auto four = new Node(4);
    one->neighbors = {two, four};
    two->neighbors = {one, three};
    three->neighbors = {two, four};
    four->neighbors = {one, three};

    auto result = cloneGraph(one);
    REQUIRE(result != nullptr);
}