// 73_matrix_zeros
// Nevin Zheng
// 8/13/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/*
 * In this O(M+N) solution we maintain a row and col array/set tracking which
 * rows and cols are zero
 * We then iterate over the rows and set thee. In the worst case this is O(MN)
 * time.
 *
 * The follow-up asks for a constant time solution. The constraints are set
 * to m,n in [1,200]. As the constraint is relatively small, we will be able
 * to use a bitset to keep track of which rows and columns should be set.
 * Technically this is still a linear time solution, but within constraints its
 * constant
 */
class SolutionBitSet {
 public:
  static constexpr size_t kMaxLen = 200;  // Given constraint
  static void setZeroes(vector<vector<int>>& matrix) {
    std::bitset<kMaxLen> z_rows;
    std::bitset<kMaxLen> z_cols;
    auto r = matrix.size();
    auto c = matrix.front().size();
    // O(MN) time
    for (auto i = 0UL; i < r; ++i) {
      for (auto j = 0UL; j < c; ++j) {
        if (matrix[i][j] == 0) {
          z_rows.set(i);
          z_cols.set(j);
        }
      }
    }
    // Fill cells if row/col bits are set
    for (auto i = 0UL; i < r; ++i) {
      for (auto j = 0UL; j < c; ++j) {
        if (z_rows[i] || z_cols[j]) matrix[i][j] = 0;
      }
    }
  }
};

/**
 * The Constant time space optimization is to use the first element of
 * a row or column as a sentinel value to indicate whether a row or col
 * should be set to zero
 */
class Solution {
 public:
  static void setZeroes(vector<vector<int>>& matrix) {
    auto r = matrix.size();
    auto c = matrix.front().size();
    bool z_first_row = false;
    bool z_first_col = false;
    // O(MN) time
    for (auto i = 0UL; i < r; ++i) {
      for (auto j = 0UL; j < c; ++j) {
        if (matrix[i][j] == 0) {  // Fill sentinel values
          matrix[i][0] = 0;
          matrix[0][j] = 0;
          if (i == 0) z_first_row = true;
          if (j == 0) z_first_col = true;
        }
      }
    }

    // Fill in [1][1]...[r-1][c-1] using sentinel values
    for (auto i = 1UL; i < r; ++i) {
      for (auto j = 1UL; j < c; ++j) {
        if (matrix[i][0] == 0 || matrix[0][j] == 0) {
          matrix[i][j] = 0;
        }
      }
    }
    // Set first row and col
    if (z_first_row)
      for (auto j = 0UL; j < c; ++j) matrix[0][j] = 0;

    if (z_first_col)
      for (auto i = 0UL; i < r; ++i) matrix[i][0] = 0;
  }
};

TEST_CASE("73::1", "[73]") {
  vector<vector<int>> matrix = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  vector<vector<int>> expected = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};
  Solution::setZeroes(matrix);
  REQUIRE(matrix == expected);
}

TEST_CASE("73::2", "[73]") {
  vector<vector<int>> matrix = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
  vector<vector<int>> expected = {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}};
  Solution::setZeroes(matrix);
  REQUIRE(matrix == expected);
}


class Solution {
public:
    void setZeroes(vector<vector<int>>& A) {
        auto R = size(A);
        auto C = size(A.front());
        bool isCol = false; // whether the first col needs to be set
        
        for(auto i=0; i<R; ++i){
            if(A[i][0] == 0) isCol = true;
            for(auto j=1; j < C; ++j) {
                if(A[i][j] == 0){
                    A[i][0] = 0;
                    A[0][j] = 0;
                }
            }
        }
        
        // Fill in the rows and cols
        for(auto i=1; i< R; ++i){
            for(auto j=1; j<C; ++j){
                if(A[i][0]==0 || A[0][j] == 0) {
                    A[i][j] = 0;
                }
            }
        }
        
        // Check if the first row needs to be set
        if(A[0][0] == 0){
            for(auto i=0; i< C; ++i){
                A[0][i] = 0;
            }
        }
        
        if(isCol) {
            for(auto i=0; i<R;++i){
                A[i][0] = 0;
            }
        }
        
    }
};