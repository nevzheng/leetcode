// A first naive DFS/BFS Solution is correct, but gives TLE in larger inputs
// Created by Nevin Zheng on 7/15/21.
//
#include <catch2/catch.hpp>
#include <vector>
using namespace std;


//Matrix makeAdjMatrix(int n, const Matrix &flights) {
//    Matrix adj(n, vector(n, 0));
//    for (auto &e : as_const(flights)) {
//        auto [u, v, w] = std::tie(e[0], e[1], e[2]);
//        adj[u][v] = w;
//    }
//    return adj;
//}


//void dfs(const AdjList &adj, int &minCost, int price, int src, int dst, int depth) {
//    if (depth < 0 || price > minCost) return;
//    if (src == dst) {
//        minCost = min(minCost, price);
//    } else {
//        for(auto &e: as_const(adj[src])){
//            auto [v,w] = e;
//            dfs(adj, minCost, price + w, v, dst, depth-1);
//        }
//    }
//}

//int findCheapestPrice(int n, const vector<vector<int>> &flights, int src, int dst, int k) {
//    auto adj = makeAdjList(n, flights);
//    // At most 1 stop => at most 2 hops
//    int minCost = std::numeric_limits<int>::max();
//    dfs(adj, minCost, 0, src, dst, k + 1);
//    return minCost == std::numeric_limits<int>::max() ? -1 : minCost;
//}
using Matrix = vector<vector<int>>;
using AdjList = vector<vector<pair<int, int>>>;

AdjList makeAdjList(int n, const Matrix &flights) {
    AdjList adj(n);
    for (auto &e : as_const(flights)) {
        auto [u, v, w] = std::tie(e[0], e[1], e[2]);
        adj[u].emplace_back(v, w);
    }
    return adj;
}
/**
 * Return the Minimum Cost of flight from src to dst with at most K Flights
 * @param n Number of Cites
 * @param flights Edge List of [u, v, cost]
 * @param src Starting City
 * @param dst Ending City
 * @param K Max number of Flights
 * @return
 */
int findCheapestPrice(int n, const vector<vector<int>> &flights, int src, int dst, int K) {
    auto k = K + 1;                    // At most K Stops = > k+1 hops
    auto adj = makeAdjList(n, flights);// Convert to Adjacency List;
    int MAX = 10e5;                    // Avoid Overflow when adding
    vector dp(n, vector(k + 1, MAX));  // dp[i][j] = minCost to City i with at most j hops
    dp[src][0] = 0;                    // Initialization Cost to get to src with 0 hops is 0

    for (auto i = 0; i < k; i++) {    // Hope
        for (auto j = 0; j < n; j++) {//cities nodes
            // Iterate over all edges
            for (auto [v, w] : as_const(adj[j])) {
                // Cost to get to city v in 1 more hop is either preexisting value
                // Or path through current city plus the weight
                dp[v][i + 1] = min(dp[v][i + 1], dp[j][i] + w);
            }
        }
    }
    // Answer is min across all dp[dst][k]
    if (auto min_elem = *min_element(begin(dp[dst]), end(dp[dst])); min_elem != MAX) {
        return min_elem;
    }
    return -1;
}


TEST_CASE("787_example1") {
    auto n = 3;
    Matrix flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    auto src = 0;
    auto dst = 2;
    auto k = 1;
    auto expected = 200;
    REQUIRE(findCheapestPrice(n, flights, src, dst, k) == expected);
}

TEST_CASE("787_example2") {
    auto n = 3;
    Matrix flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    auto src = 0;
    auto dst = 2;
    auto k = 0;
    auto expected = 500;
    REQUIRE(findCheapestPrice(n, flights, src, dst, k) == expected);
}
