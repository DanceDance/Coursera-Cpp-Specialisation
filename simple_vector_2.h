#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() : data_(nullptr), size_(0), capacity_(0) {}
  explicit SimpleVector(size_t size) : data_(new T[size]), size_(size), capacity_(size) {
  }

  ~SimpleVector() {
    if (data_ != nullptr)
      delete[] data_;
  }

  T& operator[](size_t index) {
    return data_[index];
  }

  T* begin() {
    return data_;
  }

  T* end() {
    return data_ + size_;
  }

  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return capacity_;
  }

  void PushBack(const T& value) {
    if (size_ == capacity_) {
      if (capacity_ == 0) {
        data_ = new T[1];
        capacity_ = 1;
      } else {
        size_t new_capacity = max(static_cast<size_t>(1), capacity_ * 2);
        T* new_data = new T[new_capacity];
        copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
      }
    }
    data_[size_++] = value;
  }

  void PushBack(T&& value) {
    if (size_ == capacity_) {
      if (capacity_ == 0) {
        data_ = new T[1];
        capacity_ = 1;
      } else {
        size_t new_capacity = max(static_cast<size_t>(1), capacity_ * 2);
        T* new_data = new T[new_capacity];
        move(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
      }
    }
    data_[size_++] = move(value);
  }

private:
  T* data_;
  size_t size_;
  size_t capacity_;
};
