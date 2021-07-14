//
// Created by Nevin Zheng on 7/14/21.
//
// We can solve this problem by attempting to perform a Topological Sorting of the graph
// If a topological sort does not exist, then we can return false. If it exists we can return true
// There are two main algorithms for top sorting. One is khan's algorithm. Another is a DFS bases algo
// Both run in O(V+E) time.
// This problem only asks us to return true or false. We don't need the whole top sort.
// One thing to note is that we can just use DFS to look for a cycle in the graph.
// We'll use a DFS+ Coloring approach which will run in O(V+E) time

#include <vector>
using namespace std;

enum class Color {
    White,
    Gray,
    Black
};

using Matrix = vector<vector<int>>;

/**
 * Detects a Cycle in a graph
 * @param adj
 * @param colors
 * @param root
 * @return True if DAG, False if not DAG
 */
bool dfs(const Matrix &adj, vector<Color> &colors, int root) {
    auto &col = colors[root];
    if (col == Color::Black) return true;// DFS called on completed Node. OK
    if (col == Color::Gray) return false;// Node in Call Stack Return

    col = Color::Gray;
    auto neighbors = adj[root];
    if (std::any_of(cbegin(neighbors), cend(neighbors),
                     [&](auto v) {
                         return !dfs(adj, colors, v);
                     })) {
        return false;
    };
    col = Color::Black;
    return true;
}

bool canFinish(int n, const Matrix &prereq) {
    // Convert into an adjacency List, O(E) time
    Matrix adj(n, vector<int>());
    for (auto e : as_const(prereq)) {
        auto [u, v] = std::tie(e.front(), e.back());
        adj[u].push_back(v);
    }
    vector<Color> colors(n, Color::White);
    for (auto i = 0; i < n; i++) {
        if (colors[i] == Color::White) {
            if (!dfs(adj, colors, i)) return false;
        }
    }
    return true;
}