#include "test_runner.h"

#include <utility>
#include <cstddef>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class Deque {
public:
  bool Empty() const {
    return front_.empty() && back_.empty();
  }

  size_t Size() const {
    return front_.size() + back_.size();
  }

  T& operator[](size_t index) {
    return At(index);
  }

  const T& operator[](size_t index) const {
    return At(index);
  }

  T& At(size_t index) {
    if (index >= Size())
      throw out_of_range("Index is out of range: " + to_string(index));
    if (index < front_.size())
      return front_[(int)front_.size() - index - 1];
    return back_[(int)index - front_.size()];
  }

  const T& At(size_t index) const {
    if (index >= Size())
      throw out_of_range("Index is out of range: " + to_string(index));
    if (index < front_.size())
      return front_.at((int)front_.size() - index - 1);
    return back_.at((int)index - front_.size());
  }

  T& Front() {
    return At(0);
  }

  const T& Front() const {
    return At(0);
  }

  T& Back() {
    return At((int)Size() - 1);
  }

  const T& Back() const {
    return At((int)Size() - 1);
  }

  void PushFront(const T& value) {
    front_.push_back(value);
  }

  void PushBack(const T& value) {
    back_.push_back(value);
  }

private:
  vector<T> front_;
  vector<T> back_;
};

void TestDeque() {
  {
    Deque<int> dq;
    ASSERT(dq.Empty());
    ASSERT_EQUAL(dq.Size(), 0u);
    dq.PushFront(0);
    dq.PushFront(2);
    ASSERT_EQUAL(dq.Front(), 2);
    ASSERT_EQUAL(dq.Back(), 0);
    ASSERT(!dq.Empty());
    ASSERT_EQUAL(dq.Size(), 2u);
    ASSERT_EQUAL(dq[0], 2);
    ASSERT_EQUAL(dq[1], 0);
    dq.PushBack(5);
    dq.PushBack(6);
    dq.PushBack(7);
    ASSERT_EQUAL(dq.Size(), 5u);
    ASSERT_EQUAL(dq[2], 5);
    ASSERT_EQUAL(dq[3], 6);
    ASSERT_EQUAL(dq.Front(), 2);
    ASSERT_EQUAL(dq.Back(), 7);
  }
  {
    Deque<int> dq;
    try {
      dq[1];
    } catch (out_of_range& ex) {
      ASSERT_EQUAL(ex.what(), string("Index is out of range: 1"));
    }
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestDeque);
  return 0;
}
