// 1041_robot_bounded_in_circle
// Nevin Zheng
// 7/22/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

static const int kEast = 0;
static const int kNorth = 90;
static const int kQuarterTurn = 90;
static const int kWest = 180;
static const int kSouth = 270;
static const int kMod = 360;

using X = int;
using Y = int;
using Theta = int;
using Displacement = tuple<X, Y, Theta>;
Displacement computeDisplacement(const string& instructions) {
  auto x{0};
  auto y{0};
  auto theta{kNorth};  // Initial theta is +90 degrees north
  for (auto c : instructions) {
    if (c == 'L') {
      theta = (theta + kQuarterTurn) % kMod;
    } else if (c == 'R') {
      // Avoid negative thetas
      theta = theta ? theta - kQuarterTurn : kSouth;
    } else if (c == 'G') {
      if (theta == kEast)
        x++;
      else if (theta == kNorth)
        y++;
      else if (theta == kWest)
        x--;
      else if (theta == kSouth)
        y--;
    }
  }
  return {x, y, theta};
}

bool isRobotBounded(const string& instructions) {
  auto [x, y, theta] = computeDisplacement(instructions);
  fmt::print("{}, {}, {}", x, y, theta);
  if (x == 0 and y == 0) return true;  // zero displacement
  if (theta != kNorth) return true;    //  not facing north
  return false;
}

TEST_CASE("1041ex1", "[1041]") {
  const auto* input = "GGLLGG";
  auto expected = true;
  REQUIRE(isRobotBounded(input) == expected);
}

TEST_CASE("1041ex2", "[1041]") {
  const auto* input = "GG";
  auto expected = false;
  REQUIRE(isRobotBounded(input) == expected);
}

TEST_CASE("1041ex3", "[1041]") {
  const auto* input = "GL";
  auto expected = true;
  REQUIRE(isRobotBounded(input) == expected);
}

TEST_CASE("1041ex4", "[1041]") {
  const auto* input = "GLRLGLLGLGRGLGL";
  auto expected = true;
  REQUIRE(isRobotBounded(input) == expected);
}