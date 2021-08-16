// five_star_sellers
// Nevin Zheng
// 8/4/21

// Five-Star Sellers
// Given the number of five-star and total reviews for each product a company
// sells, as well as the threshold percentage, what is the minimum number of
// additional five-star reviews the company needs to become five-star seller.
// public static int fiveStarReviews(List<List<Integer>> productRatings, int
// ratingsThreshold){
//}
// Examples 1:
// Input:
//  noOfProduct = 3
//      productRatings = [[4,4],[1,2],[3,6]]
//      => here [1,2] indicates =>[1 (five star reviews) ,2 (total reviews)].
//      threshold = 77
//      Output: 3
//      Explanation:
//  We need to get the seller reach the threshold with minimum number of
//  additional five-star reviews. Before we add more five-star reviews, the
//  percentage for this seller is ((4/4) + (1/2) + (3/6)) /3 = 66.66%
//  If we add a five-star review to 2nd product, ((4/4) + (2/3) + (3/6))/3
//  = 72.22%
//  If we add another five-star review to 2nd product, ((4/4) + (3/4) +
//  (3/6))/3 = 75%
//   If we add a five-star review to 3rd product, ((4/4) + (3/4) +
//   (4/7))/3 = 77.38%
//   At this point, 77% (threshold) is met. Therefore, answer
//   is 3 (because that is the minimum five-star reviews we need
//   to add, to get the seller reach the threshold). Constraints:
//  1 <= productRatings.size() <=200
//  In product ratings, [five-star, total], five-star <= 100, total <= 100
//  1 <= ratingsThreshold < 100
//  productRatings contains only non-negative integers.

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * For This problem, we want to develop a way to pick the element with
 * the largest marginal gain. EX the change in the score
 * Given a score [x, y] with x the number of 5 stars and y the total
 * the marginal gain in improving the score is ((x+1)/(y+1)) - ((x)/(y))
 * We can find the minimal number of stars required by picking the element
 * with the largest marginal gain and improving the current score until we
 * cross the threshold.
 * We're working with doubles so there might be some edge cases, but we can
 * fix those after we prove the concept.
 * @param ratings
 * @param threshold
 * @return
 */
int fiveStarSellers(const vector<vector<int>>& ratings, int threshold) {
  int additional_stars = 0;
  // Required Threshold is given as a percentage, we need to convert to a
  // decimal by dividing by 100. We'll also convert from a decimal into a sum
  // the number of reviews is constant, so we can multiply to convert
  // to a required sum of individual review scores.
  int num_reviews = static_cast<int>(ratings.size());
  double thr = threshold / 100. * num_reviews;

  // Starting score sum of x/y for all x,y in ratings
  double score = transform_reduce(ratings.begin(), ratings.end(), 0.0, plus<>(),
                                  [](const vector<int>& rating) {
                                    return static_cast<double>(rating.front()) /
                                           static_cast<double>(rating.back());
                                  });

  // Create a comparison function that maximizes marginal gain
  auto cmp = [](const vector<int>& a, const vector<int>& b) {
    // for rating [x,y], marginal gain = (x+1)/(y+1) - (x)/(y);
    auto marginal_gain = [](const vector<int>& x) {
      double n = x.front();
      double d = x.back();
      return ((n + 1) / (d + 1)) - ((n) / (d));
    };
    // Return the larger marginal gain;
    return marginal_gain(a) < marginal_gain(b);
  };

  // PQ with the given comparator. Uses Heapify in O(N) time
  std::priority_queue pq(cmp, ratings);

  // Keep improving the score until we cross the threshold
  // T = # stars * lg(N). O(N) space.
  // Let's say in the worst case # stars is linear.
  while (score < thr) {
    auto cur = pq.top();  // pick element that will improve score the most
    pq.pop();
    ++additional_stars;
    double n = cur[0];
    double d = cur[1];
    score -= (n / d);                   // Remove old
    score += (n + 1) / (d + 1);         // Add improved to score
    pq.push({cur[0] + 1, cur[1] + 1});  // Push improved
  }
  return additional_stars;
}

TEST_CASE("ex1", "[five_star]") {
  const vector<vector<int>> product_ratings = {{4, 4}, {1, 2}, {3, 6}};
  const int threshold = 77;
  const int expected = 3;
  REQUIRE(fiveStarSellers(product_ratings, threshold) == expected);
}