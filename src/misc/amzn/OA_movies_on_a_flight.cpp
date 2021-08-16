// OA_movies_on_a_flight
// Nevin Zheng
// 8/10/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

// https://leetcode.com/discuss/interview-question/313719/Amazon-or-Online-Assessment-2019-or-Movies-on-Flight

// Question: You are on a flight and wanna watch two movies during this flight.
// You are given List<Integer> movieDurations which includes all the movie
// durations. You are also given the duration of the flight which is d in
// minutes. Now, you need to pick two movies and the total duration of the two
// movies is less than or equal to (d - 30min).
//
// Find the pair of movies with the longest total duration and return they
// indices. If multiple found, return the pair with the longest movie.

/**
 * This question is a variation of two sum where we have to find the closest
 * sum to target.
 * We'll sort the movies, then use a two pointer technique to get
 * as close to the duration without exceeding it
 *
 * Runs in linear time and memory
 * @param A
 * @param tgt
 * @return
 */
vector<int> findPair(vector<int> A, int tgt) {
  const int k_margin = 30;
  tgt -= k_margin;  // Set tg/max val to d-30;
  auto n = static_cast<int>(A.size());
  // need to handle dupes with vec
  // More than 2 is possible, but we can just return any index
  unordered_map<int, vector<int>> indices;
  for (auto i = 0; i < n; ++i) {
    indices[A[i]].push_back(i);  // Stash original indices;
  }
  std::sort(A.begin(), A.end());  // Sort A

  auto g_diff = INT_MAX;
  vector<int> idx = {-1, -1};
  auto l = 0;
  auto r = n - 1;

  while (l < r) {
    auto sum = A[l] + A[r];
    auto diff = tgt - sum;
    if (sum <= tgt) {
      if (diff <= g_diff) {
        // Set if invalid, if closer, or if the movie is longer
        // it's sorted so idx[1] is larger
        if (idx[0] == -1 || diff < g_diff || A[r] > A[idx[1]]) idx = {l, r};
        g_diff = diff;
      }
      ++l;  // Make Larger/Keep Searching in case better pair
    } else {
      --r;  // Too Big, Shrink sum and don't record
    }
  }

  // Translate the indices
  if (idx.front() == -1) return idx;      // Couldnt find sum
  if (A[idx.front()] == A[idx.back()]) {  // Same values
    idx = {indices[A[idx[0]]].front(), indices[A[idx[1]]].back()};
  } else {
    idx = {indices[A[idx[0]]].front(), indices[A[idx[1]]].front()};
  }
  return idx;
}

TEST_CASE("OA::movies_on_a_flight::1", "[oaMoviesOnAFlight]") {
  const vector<int> movie_durations = {90, 85, 75, 60, 120, 150, 125};
  const int duration = 250;
  const vector<int> expected = {0, 6};
  REQUIRE(findPair(movie_durations, duration) == expected);
}

TEST_CASE("OA::movies_on_a_flight::2", "[oaMoviesOnAFlight]") {
  const vector<int> movie_durations = {90, 85, 75, 60, 155, 150, 125};
  const int duration = 250;
  const vector<int> expected = {3, 4};
  REQUIRE(findPair(movie_durations, duration) == expected);
}

TEST_CASE("OA::movies_on_a_flight::3", "[oaMoviesOnAFlight]") {
  const vector<int> movie_durations = {90, 85, 75, 60, 120, 110, 110, 150, 125};
  const int duration = 250;
  const vector<int> expected = {5, 6};
  REQUIRE(findPair(movie_durations, duration) == expected);
}
