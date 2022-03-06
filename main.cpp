#include "test_runner.h"

#include <utility>
#include <cstddef>
using namespace std;

template<typename T>
class Table {
public:
  Table(size_t rows, size_t cols) : table(rows, vector<T>(cols)) {}

  pair<size_t, size_t> Size() const {
    if (Rows() == 0 || Cols() == 0)
      return {0, 0};
    return {Rows(), Cols()};
  }

  void Resize(size_t new_rows, size_t new_cols) {
    table.resize(new_rows);
    for (auto &row : table)
      row.resize(new_cols);
  }

  vector<T>& operator[] (int row) {
    return table[row];
  }

  const vector<T>& operator[] (int row) const {
    return table[row];
  }

  size_t Rows() const {
    return table.size();
  }

  size_t Cols() const {
    if (table.empty())
      return 0;
    return table[0].size();
  }

private:
  vector<vector<T>> table;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
