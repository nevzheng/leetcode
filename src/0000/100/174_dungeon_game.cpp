// 174_dungeon_game
// Nevin Zheng
// 7/19/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

using Dungeon = vector<vector<int>>;

using dpTable = std::vector<std::vector<int>>;
//    static auto dungeon_helper(size_t row, size_t col, const Dungeon &dungeon, dpTable &dp) -> int {
//        // Base Case
//        if (row == dungeon.size() - 1 and col == dungeon.front().size() - 1) {
//            // At the end of our recursion, our sum will either be greater than 0, in which case we need just 1 HP
//            // Else it will be 1 more than abs of the damage taken.
//            // Take path that minimizes damage, then
//            auto result = dungeon[row][col];
//            return result > 0 ? 1 : abs(result) + 1;
//        }
//        // Cache Hit
//        if (auto found = dp[row][col]; found != std::numeric_limits<int>::min()) {
//            return found;
//        }
//        // Last Row
//        if (row == dungeon.size() - 1) {
//            // We either take damage, die, and start over, or keep our current value
//            return std::max(1, dungeon_helper(row, col + 1, dungeon, dp) - dungeon[row][col]);
//        }
//
//        // Last Col
//        if (col == dungeon.front().size() - 1) {
//            // If you have more health than you need, you can decrease the amount of health you can return
//            // As it will be added
//            return std::max(1, dungeon_helper(row + 1, col, dungeon, dp) - dungeon[row][col]);
//        }
//
//        // Default Case
//        auto go_down = dungeon_helper(row + 1, col, dungeon, dp);
//        auto go_right = dungeon_helper(row, col + 1, dungeon, dp);
//        return dp[row][col] = std::max(1, std::min(go_down, go_right) - dungeon[row][col]);
//    }
//
//    static int calculateMinimumHP(Dungeon &dungeon) {
//        // Create an dp table initialized to int_min
//        dpTable dp(dungeon.size(), std::vector<int>(dungeon.front().size(), std::numeric_limits<int>::min()));
//        return dungeon_helper(0, 0, dungeon, dp);
//    }

static auto calculateMinimumHP(Dungeon &dungeon) -> int {
    dpTable dp(dungeon.size(), std::vector<int>(dungeon.front().size(), std::numeric_limits<int>::min()));
    int64_t max_row = dungeon.size() - 1;
    int64_t max_col = dungeon.front().size() - 1;
    // This Bottom up DP approach will fill row by row in reverse order from the princess tile
    for (auto it = max_row; it >= 0; --it) {
        for (auto jt = max_col; jt >= 0; --jt) {
            fmt::print("Filling in {},{}\n", it, jt);
            auto tile_val = dungeon[it][jt];
            if (it == max_row and jt == max_col) {
                // Base Case at Princess tile
                // You either die and need abs(tile_val) health
                // Or its 0 / you get a pick up and don't need health to survive the tile
                dp[it][jt] = tile_val > 0 ? 0 : abs(tile_val);
                fmt::print("Case: Princess Tile: Filled: {}\n", dp[it][jt]);
            } else if (it != max_row and jt == max_col) {// Last Col
                // We can only retreive values from below
                auto go_down = dp[it + 1][jt];
                // If we go down, whats the min health to survive?
                auto diff = tile_val - go_down;
                // If difference is positive, then we don't need additional health
                dp[it][jt] = diff > 0 ? 0 : abs(diff);
                fmt::print("Case: Last Col: Filled {}\n", dp[it][jt]);
            } else if (it == max_row and jt != max_col) {// Last Row
                // If we're in the last row, we can only look at prev filled vals on right
                auto go_right = dp[it][jt + 1];
                // Similar reasoning. we need the minimum health
                auto diff = tile_val - go_right;
                dp[it][jt] = diff > 0 ? 0 : abs(diff);
                fmt::print("Case: Last Row: Filled: {}\n", dp[it][jt]);
            } else {// Default Case
                auto go_down = dp[it][jt + 1];
                auto go_right = dp[it + 1][jt];
                // Here we choose the direction that minimizes the amount of health we need
                auto choice = std::min(go_right, go_down);
                auto diff = tile_val - choice;
                dp[it][jt] = diff > 0 ? 0 : abs(diff);
                fmt::print("Case: Default Case: Filled: {}\n", dp[it][jt]);
            }
        }
    }
    // Return 1 more than the minimum health needed;
    // We could have added 1 while doing DP, but we can rephrase the question as:
    // We need 1 more health than the min HP loss across the whole board.
    // Sometimes you'll gain HP which will make up for damage taken,
    // But this is the HP that you'll need to survive.
    return dp.front().front() + 1;
}


TEST_CASE("174Example1", "[174]") {
    Dungeon dungeon = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
    REQUIRE(calculateMinimumHP(dungeon) == 7);
}

TEST_CASE("174EXAMPLE2", "[174]") {
    Dungeon dungeon = {{0, -3}};
    REQUIRE(calculateMinimumHP(dungeon) == 4);
}

TEST_CASE("174EXAMPLE3", "[174]") {
    Dungeon dungeon = {{1, -3, 3}, {0, -2, 0}, {-3, -3, -3}};
    REQUIRE(calculateMinimumHP(dungeon) == 3);
}