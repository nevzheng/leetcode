// This Problem is an extension of 207. We just add a TopSort Vector to DFS and record Nodes after ther are marked black
// Created by Nevin Zheng on 7/14/21.
//

#include <vector>

#include <catch2/catch.hpp>

using namespace std;

using Matrix = vector<vector<int>>;

enum class Color {
    White,// Unvisited,
    Gray, // Processing
    Black,// Processes
};

bool dfs(const Matrix &adj, vector<int> &topSort, vector<Color> &colors, int u) {
    auto &col = colors[u];
    if (col == Color::Black) return true;
    if (col == Color::Gray) return false;
    col = Color::Gray;// Mark Node as Processing
    for (auto neighbor : adj[u]) {
        if (!dfs(adj, topSort, colors, neighbor)) {
            return false;
        }
    }
    col = Color::Black;// Mark Node as Processed
    topSort.push_back(u);
    return true;
}
vector<int> findOrder(int numCourses, const Matrix &prerequisites) {
    Matrix adj(numCourses);
    // Convert the graph in to an Adj Matrix O(E) time and O(E+V) space
    for (auto &e : as_const(prerequisites)) {
        auto [u, v] = std::tie(e.front(), e.back());
        adj[u].push_back(v);
    }
    // Allocate a Color Array
    vector colors(numCourses, Color::White);
    vector<int> topSort;
    for (auto u = 0; u < numCourses; u++) {
        if (colors[u] == Color::White) {
            if (!dfs(adj, topSort, colors, u)) return {};
        };
    }
    return topSort;
}

TEST_CASE("210_example1", "[210]") {
    int numCourses = 4;
    Matrix prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    vector<int> expected = {0, 2, 1, 3};// OR 0,2,1,3

    auto result = findOrder(numCourses, prerequisites);
    REQUIRE(result == expected);
}