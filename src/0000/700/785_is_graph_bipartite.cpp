// 785785_is_graph_bipartite
// Nevin Zheng
// 7/19/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using AdjList = vector<vector<int>>;

enum class Color {
    Gray, // Unvisited
    White,// Visited C 0
    Black // Visited C 1
};

Color toggleColor(Color c) {
    return c == Color::White ? Color::Black : Color::White;
}
bool dfs(const AdjList &G, vector<Color> &colors, Color active, int u) {
    // Check for a conflict
    if (colors[u] != Color::Gray) {
        if (colors[u] == active) {// Visited
            return true;
        } else {
            return false;
        }
    }
    colors[u] = active;// Mark the Node
    for (auto v : G[u]) {
        if (!dfs(G, colors, toggleColor(active), v)) return false;
    }
    return true;
}

bool isBipartite(const AdjList &G) {
    auto V = G.size();
    vector colors(V, Color::Gray);
    for (auto i = 0; i < V; i++) {
        if (colors[i] != Color::Gray) continue;// Skip Already Visited Nodes
        if (!dfs(G, colors, Color::White, i)) return false;
    }
    return true;
}


TEST_CASE("785ex1", "[785]") {
    AdjList graph = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};
    auto expected = false;
    REQUIRE(isBipartite(graph) == expected);
}

TEST_CASE("785ex2", "[785]") {
    AdjList graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    auto expected = true;
    REQUIRE(isBipartite(graph) == expected);
}