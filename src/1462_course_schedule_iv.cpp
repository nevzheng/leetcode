//
// Created by Nevin Zheng on 7/13/21.
//
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace std;

using Matrix = vector<vector<int>>;

void dfs(int root, vector<bool> &visited, vector<int> &topSort, const Matrix &adj) {
    visited[root] = true;
    for (const auto x : adj[root]) {
        if (!visited[x]) dfs(x, visited, topSort, adj);
    }
    topSort.push_back(root);
}


vector<bool> checkIfPrerequisite(int numCourses,
                                 const vector<vector<int>> &prerequisites,
                                 const vector<vector<int>> &queries) {
    Matrix adj(numCourses, vector<int>());
    for (const auto &e : prerequisites) {
        auto u = e.front();
        auto v = e.back();
        adj[u].push_back(v);
    }

    vector<int> topSort;
    vector<bool> visited(numCourses, false);
    // Use DFS to obtain a topological sort
    for (auto start = 0; start < numCourses; start++) {
        if (!visited[start]) dfs(start, visited, topSort, adj);
    }
    utils::printVector(topSort);
    vector<bool> responses;
    responses.reserve(queries.size());
    for(const auto x: queries){

    }
    return responses;
}

TEST_CASE("1462_example1") {
    auto numCourses = 2;
    Matrix prerequisites = {{1, 0}};
    Matrix queries = {{0, 1}, {1, 0}};
    vector<bool> correct = {false, true};
    REQUIRE(checkIfPrerequisite(numCourses, prerequisites, queries) == correct);
}