// 567_permutation_in_string
// Nevin Zheng
// 9/2/21

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Solution {
 public:
  const static int kAsciiLowerCase{26};
  static bool checkInclusion(const string& s1, const string& s2) {
    vector<int> goal(kAsciiLowerCase);
    vector<int> cur(kAsciiLowerCase);
    for (char c : s1) goal[c - 'a']++;  // Summarize s1
    for (auto i = 0UL; i < s2.size(); i++) {
      cur[s2[i] - 'a']++;  // Update Window.
                           // Size is bounded by size of s1, shrink
      if (i >= s1.size()) cur[s2[i - s1.size()] - 'a']--;
      if (goal == cur) return true;  // Window now contains a permutation of s1
    }
    return false;
  }
};
