//
// Created by Nevin Zheng on 7/13/21.
//
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace std;

using BoolMatrix = vector<vector<bool>>;
using IntMatrix = vector<vector<int>>;

void floydWarshall(int N, BoolMatrix &dist) {
    for (auto k = 0; k < N; k++) {
        for (auto u = 0; u < N; u++) {
            for (auto v = 0; v < N; v++) {
                if (dist[u][k] and dist[k][v])
                    dist[u][v] = true;
            }
        }
    }
}

BoolMatrix makeAdjacencyMatrix(const IntMatrix &pre, int N) {// Create an adjacency matrix
    BoolMatrix adj(N, vector(N, false));
    for (auto &e : pre) {
        auto [u, v] = tie(e[0], e[1]);
        adj[u][v] = true;// Insert Backwards?
    }
    return adj;
}

/**
 * In this method, we will apply an All Source Shortest Path algorithm, specifically Floyd Warshall to compute
 * possible dependencies in N=numCourses O(N^3) time and O(V^2) space.
 * If A path exists between, there will be an non infinite/Zero entry in the Resulting Distance Matrix.
 * This will allow us to answer each query in O(1) time.
 * Our final Complexity is O(N^3) + O(numQueries) an O(n^2) space
 * @param numCourses
 * @param pre
 * @param Q
 * @return
 */
vector<bool> checkIfPrerequisite(int numCourses,
                                 const vector<vector<int>> &pre,
                                 const vector<vector<int>> &Q) {
    if (Q.empty()) return {};// Base Case No Queries
    auto N = numCourses;
    if (pre.empty()) return vector(N, false);// Base Case No prereqs
    auto dist = makeAdjacencyMatrix(pre, N);
    floydWarshall(N, dist);
    vector<bool> ans;
    std::transform(begin(Q), end(Q), back_inserter(ans),
                   [&dist](const auto &q) { return dist[q[0]][q[1]]; });
    return ans;
}


TEST_CASE("1462_ex1", "[1462]") {
    auto numCourses = 2;
    IntMatrix prerequisites = {{1, 0}};
    IntMatrix queries = {{0, 1}, {1, 0}};
    vector<bool> correct = {false, true};
    REQUIRE(checkIfPrerequisite(numCourses, prerequisites, queries) == correct);
}

TEST_CASE("1462_ex2", "[1462]") {
    auto numCourses = 5;
    IntMatrix prerequisites = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    vector<vector<int>> queries = {{0, 4}, {4, 0}, {1, 3}, {3, 0}};
    vector<bool> correct = {true, false, true, false};
    REQUIRE(checkIfPrerequisite(numCourses, prerequisites, queries) == correct);
}