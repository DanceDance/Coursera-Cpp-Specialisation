#include "test_runner.h"
#include <vector>
#include <future>
#include <cstddef>
#include <numeric>
using namespace std;

constexpr int kThreadCount = 4;

int64_t accumulate_multiple_rows(const vector<vector<int>>& matrix, size_t start_row, size_t rows) {
  int64_t res = 0;
  for (size_t i = start_row; i < min(matrix.size(), start_row + rows); i++)
    res += accumulate(matrix[i].begin(), matrix[i].end(), 0);
  return res;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  size_t rows = matrix.size();
  size_t rows_per_thread = (rows + kThreadCount - 1) / kThreadCount;
  vector<future<int64_t>> futures;
  int64_t res = 0;
  for (size_t i = 0; i < kThreadCount; i++) {
    size_t current_index = i * rows_per_thread;
    if (i == kThreadCount - 1) {
      // This thread
      res += accumulate_multiple_rows(matrix, current_index, rows_per_thread);
    } else {
      futures.push_back(async([current_index, rows_per_thread, &matrix] {
        return accumulate_multiple_rows(matrix, current_index, rows_per_thread);
      }));
    }
  }
  for (auto &x : futures)
    res += x.get();
  return res;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
