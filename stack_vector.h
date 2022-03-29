#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) : size_(a_size) {
    if (a_size > N)
      throw invalid_argument("");
  }

  T& operator[](size_t index) {
    return arr_[index];
  }
  const T& operator[](size_t index) const {
    return arr_[index];
  }

  T* begin() {
    return &arr_[0];
  }
  T* end() {
    return &arr_[size_];
  }
  const T* begin() const {
    return &arr_[0];
  }
    
  const T* end() const {
    return &arr_[size_];
  }

  size_t Size() const {
    return size_;
  }
  size_t Capacity() const {
    return N;
  }

  void PushBack(const T& value) {
    if (size_ == N)
      throw overflow_error("");
    arr_[size_++] = value;
  }
    
  T PopBack() {
    if (size_ == 0) {
      throw underflow_error("");
    }
    return arr_[--size_];
  }

private:
  size_t size_;
  array<T, N> arr_;
};

