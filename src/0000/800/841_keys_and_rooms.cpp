// 841_keys_and_rooms
// Nevin Zheng
// 7/18/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

template<typename T>
using Grid = vector<vector<T>>;

enum class Color {
    White,
    Gray,
    Black,
};

void can_visit_all(const Grid<int> &G, vector<Color> &colors, int u) {
    auto &c = colors[u];
    if (c != Color::White) return;// Gray usually mean a cycle, but its ok here
    c = Color::Gray;
    for (auto v : G[u]) can_visit_all(G, colors, v);
    c = Color::Black;// Mark Done and return
}

/**
 * To solve this problem we will do a depth first search from node 0
 * this will take O(E+V) time
 * If after the search a node remains unvisited then it is not connected.
 * We might run into some trouble if the graph is larger, but we should be able to make it with linear complexity
 * @param G
 * @return
 */
bool canVisitAllRooms(const Grid<int> &G) {
    auto N = G.size();// N rooms
    vector<Color> colors(N, Color::White);
    can_visit_all(G, colors, 0);
    // Gray Should be Ok for this application?
    return all_of(begin(colors), end(colors), [](auto c) { return c != Color::White; });
}


TEST_CASE("841ex1", "[841]") {
    Grid<int> input = {{1}, {2}, {3}, {}};
    auto expected = true;
    REQUIRE(canVisitAllRooms(input) == expected);
}

TEST_CASE("841ex2", "[841]") {
    Grid<int> input = {{1, 3}, {3, 0, 1}, {2}, {0}};
    auto expected = false;
    REQUIRE(canVisitAllRooms(input) == expected);
}