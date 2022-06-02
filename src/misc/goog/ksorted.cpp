#include <priority_queue>
#include <vector>
using namespace std;

vector<int> sortKSortedArray(vector<int> A, int k) {
  std::priority_queue<int> pq;
  int i = 0;
  for (; i < k; ++i) {
    pq.push(A[i]);
  }
  for (auto j = 0; j < size(A); ++j) {
    A[j] = pq.top();
    pq.pop();
    if (i < size(A)) pq.push(A[i++]);
  }
  return A;
}

int main() {
  std::vector<int> A{3, 2, 1, 5, 4, 7, 6, 5};
  int k = 3;
  sortKSortedArray(A, k);
}