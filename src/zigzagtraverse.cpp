#include <vector>

using namespace std;

vector<int> zigzagTraverse(vector<vector<int>> A) {
  std::vector<int> ans;
  int R = size(A) - 1;
  int C = size(A[0]) - 1;
  int r = 0;
  int c = 0;

  bool down = true;

  while (0 <= r && r <= R && 0 <= c && c <= C) {
    ans.push_back(A[r][c]);

    if (down) {
      if (r == R || c == 0) {  // touched last row or first column. change direction
        down = false;          // finished scan set for next scan
        if (r == R) {
          ++c;
        } else {
          ++r;
        }
      } else {  // go down left
        ++r;
        --c;
      }
    } else {  // going up
      if (r == 0 || c == C) {
        down = true;
        if (c == C) {
          ++r;
        } else {
          ++c;
        }
      } else {
        --r;
        ++c;
      }
    }
  }
  return ans;
}
