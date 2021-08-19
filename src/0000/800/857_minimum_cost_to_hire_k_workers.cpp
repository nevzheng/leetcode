// 857_minimum_cost_to_hire_k_workers
// Nevin Zheng
// 8/18/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

struct Worker {
  int quality;
  int wage;
  Worker(int quality, int wage) : quality(quality), wage(wage) {}
  [[nodiscard]] double ratio() const {
    return static_cast<double>(wage) / quality;
  }
};

/**
 * Assume we take a ratio of wage / quality.
 * we need to ensure that workers get paid their minimum wage.
 * we also observe that if we pick a "captain" to set the highest wage
 * then workers with lower ratios are happy getting paid the appropriate portion
 * of the wage set by the captain.
 * "You can choose a captain ratio and workers with lower ratios will be happy"
 * Another observation is that if the captain sets the ratio, then we need to
 * pick the captain with the lowest quality. As the the ratio wage/ quality
 * represents a price per unit quality and we want to pay the the least for k
 * workers and since the workers under the captain in ratio are happy being paid
 * a portion of the captains minimum wage, the total will be minimized if we
 * choose the k lowest quality workers
 */
class Solution {
 public:
  static double mincostToHireWorkers(const vector<int>& quality,
                                     const vector<int>& wage, int k) {
    vector<Worker> workers;
    transform(quality.begin(), quality.end(), wage.begin(),
              back_inserter(workers),
              [](int q, int w) { return Worker(q, w); });

    // Sort by minimum ratio
    std::sort(
        workers.begin(), workers.end(),
        [](const Worker& a, const Worker& b) { return a.ratio() < b.ratio(); });

    // We then want to iterate over all the minimum ratios
    // in order to determine the k  lowest quality workers
    // we create a max heap w/ key as quality, and pop the top elements
    // leaving the k lowest quality workers
    // We want to pay the LEAST but have to pay the captain the most
    // so we should make sure to pick the cheapest captain.
    double ans = DBL_MAX;
    double qsm = 0.;
    priority_queue<int> pq;
    // Find  the lowest qualities
    for (auto& w : workers) {
      qsm += w.quality;
      pq.push(w.quality);
      if (static_cast<int>(pq.size()) > k) qsm -= pq.top(), pq.pop();
      if (static_cast<int>(pq.size()) == k) ans = min(ans, qsm * w.ratio());
    }
    return ans;
  }
};

constexpr double kEpsilon = 1e-5;

TEST_CASE("857::1", "[857]") {
  vector<int> quality{10, 20, 5};
  vector<int> wage{70, 50, 30};
  const int k = 2;
  const double expected = 105.00000;
  auto res = Solution::mincostToHireWorkers(quality, wage, k);
  REQUIRE(abs(res - expected) < kEpsilon);
}

TEST_CASE("857::2", "[857]") {
  vector<int> quality{3, 1, 10, 10, 1};
  vector<int> wage{4, 8, 2, 2, 7};
  const int k = 3;
  const double expected = 30.66667;
  auto res = Solution::mincostToHireWorkers(quality, wage, k);
  REQUIRE(abs(res - expected) < kEpsilon);
}
