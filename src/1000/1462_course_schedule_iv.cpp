//
// Created by Nevin Zheng on 7/13/21.
//
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

using namespace std;

/**
 * There are a few apporoaches the the problem.
 * Firstly you could use a DFS for each query, but that that does not scale for large values of N
 * Secondly you could use a Topological sort, but if you would have to structure it properly
 * to avoid mistaking being earlier in the top sort with being a dependency.
 * The simplest approach I can think of is to use an All Pairs Shortest Path algorithm such as Floyd Warshal to
 * precompute the distance Matrix in O(N^3) time which then allows us to answer each query in constant time
 * Basically if there is a dependency from u to v there will be a zero value in dist[u][v]
 * We can also just use boolean values in our FW algo to save some memory.
 */
using IntMatrix = vector<vector<int>>;
using BoolMatrix = vector<vector<bool>>;

BoolMatrix makeAdjacencyMatrix(const IntMatrix &P, int N) {
    BoolMatrix adj(N, vector(N, false));
    for (auto &e : P) adj[e[0]][e[1]] = true;
    return adj;
}

void floydWarshall(BoolMatrix &dist, int N) {
    for (auto k = 0; k < N; k++) {
        for (auto u = 0; u < N; u++) {
            for (auto v = 0; v < N; v++) {
                if (dist[u][k] and dist[k][v]) dist[u][v] = true;
            }
        }
    }
}

vector<bool> checkIfPrerequisite(int N, const IntMatrix &P, IntMatrix &Q) {
    auto dist = makeAdjacencyMatrix(P, N);
    floydWarshall(dist, N);
    vector<bool> ans;
    transform(begin(Q), end(Q), back_inserter(ans), [&dist](const auto &q) { return dist[q[0]][q[1]]; });
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
    IntMatrix queries = {{0, 4}, {4, 0}, {1, 3}, {3, 0}};
    vector<bool> correct = {true, false, true, false};
    REQUIRE(checkIfPrerequisite(numCourses, prerequisites, queries) == correct);
}