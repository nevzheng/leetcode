//
// Created by Nevin Zheng on 7/13/21.
//
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;


using Matrix = vector<vector<int>>;
using AdjList = vector<vector<int>>;
class Solution {
public:
    enum class Color {
        None,
        Red,
        Blue
    };

    void printVector(const vector<Color> &v) {
        for (const auto &x : v) {
            string c;
            switch (x) {
                case Color::Red:
                    c = "Red";
                    break;
                case Color::Blue:
                    c = "Blue";
                    break;
                case Color::None:
                    c = "None";
                    break;
            }
            cout << c;
            cout << ' ';
        }
        cout << '\n';
    }
    static Matrix makeAdjacencyMatrix(int n, const vector<vector<int>> &edgeList) {
        Matrix adj(n, vector(n, 0));
        for (const auto &edge : edgeList) {
            // People are numbered from 1 to n
            auto v = edge.back() - 1;
            auto u = edge.front() - 1;
            adj[u][v] = 1;
            adj[v][u] = 1;
        }
        return adj;
    }

    Color toggleColor(Color c) {
        switch (c) {
            case Color::Blue:
                return Color::Red;
            case Color::Red:
                return Color::Blue;
            default:
                exit(1);
        }
    }
    //    bool colorGraph(Matrix adj, int n, vector<Color>& colors, int start) {
    //        queue<int> q;
    //        q.push(start);// Start at Node 0;
    //        colors[start] = Color::Red;
    //
    //        while (!q.empty()) {
    //            auto u = q.front();
    //            q.pop();
    //            // Find all non-colored adjacent vertices
    //            for (int v = 0; v < n; v++) {
    //                if (adj[u][v] && colors[v] == Color::None) {
    //                    colors[v] = toggleColor(colors[u]);          // Set to the Alternate Color of u;
    //                    q.push(v);                                   // Explore this node next;
    //                } else if (adj[u][v] && colors[u] == colors[v]) {// Conflict Found not bipartite
    //                    return false;
    //                }
    //            }
    //        }
    //        return true;
    //    }

    AdjList makeAdjacencyList(int n, const Matrix &edges) {
        AdjList adj(n, vector<int>());
        for (const auto &e : edges) {
            // People are numbered from 1.
            auto u = e.front()-1;
            auto v = e.back()-1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return adj;
    }
    bool colorGraph(Matrix adj, int n, vector<Color> &colors, int start) {
        queue<int> q;
        q.push(start);// Start at Node 0;
        colors[start] = Color::Red;

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            // Find all non-colored adjacent vertices
            for (const auto v : adj[u]) {
                if (colors[v] == Color::None) {
                    colors[v] = toggleColor(colors[u]);          // Set to the Alternate Color of u;
                    q.push(v);                                   // Explore this node next;
                } else if (colors[u] == colors[v]) {// Conflict Found not bipartite
                    return false;
                }
            }
        }
        return true;
    }
    bool possibleBipartition(int n, const vector<vector<int>> &dislikes) {
        auto adjList = makeAdjacencyList(n, dislikes);
        vector colors(n, Color::None);// 0 uncolored, 1 red, 2 blue;
        bool result = true;
        for (auto start = 0; start < n; start++) {
            if (colors[start] == Color::None) {
                result &= colorGraph(adjList, n, colors, start);
                if(!result) return false;
            }
            printVector(colors);
        }
        return result;
    }
};

TEST_CASE("886_example1") {
    Solution sol;
    Matrix v{{1, 2}, {1, 3}, {2, 4}};
    auto n = 4;
    REQUIRE(sol.possibleBipartition(n, v) == true);
}

// This Graph is disconnected so we have to make sure that we explore all components
TEST_CASE("886_example2") {
    Solution sol;
    Matrix v{{1, 2}, {3, 4}, {4, 5}, {3, 5}};
    int n = 5;
    REQUIRE(sol.possibleBipartition(n, v) == false);
}