#pragma once
#include "base_container.h"
#include "vector_iterator.hpp"
#include <cstddef>
#include <iostream>

template <typename T> class DynamicContainer : public BaseContainer<T> {
public:
  explicit DynamicContainer(size_t N = 5, float resize_scale = 1.5)
      : data_{new T[N]}, capacity_{N}, next_{0}, resize_scale_{resize_scale} {};

  ~DynamicContainer() override { delete[] data_; }

  // Copy ctor
  DynamicContainer(const DynamicContainer &other) {
    std::cout << "DynamicContainer:: Copy ctor" << std::endl;
    capacity_ = other.capacity_;
    next_ = other.next_;
    resize_scale_ = other.resize_scale_;
    data_ = new T[other.capacity_];
    for (size_t i = 0; i < next_; i++) {
      data_[i] = other.data_[i];
    }
  }

  // Copy assignment operator
  DynamicContainer &operator=(const DynamicContainer &rhs) {
    std::cout << "DynamicContainer:: Copy assignment operator" << std::endl;
    capacity_ = rhs.capacity_;
    next_ = rhs.next_;
    resize_scale_ = rhs.resize_scale_;
    delete[] data_;
    data_ = new T[rhs.capacity_];
    for (int i = 0; i < next_; i++) {
      data_[i] = rhs.data_[i];
    }

    return *this;
  }

  // Move ctor
  DynamicContainer(DynamicContainer &&other) noexcept {
    std::cout << "DynamicContainer:: Move ctor" << std::endl;
    capacity_ = other.capacity_;
    next_ = other.next_;
    resize_scale_ = other.resize_scale_;
    data_ = other.data_;

    other.data_ = nullptr;
    other.capacity_ = 0;
    other.next_ = 0;
  }

  // Move assignment operator
  DynamicContainer &operator=(DynamicContainer &&rhs) noexcept {
    std::cout << "DynamicContainer:: Move assignment operator" << std::endl;
    capacity_ = rhs.capacity_;
    next_ = rhs.next_;
    resize_scale_ = rhs.resize_scale_;
    delete[] data_;
    data_ = rhs.data_;

    rhs.data_ = nullptr;
    rhs.capacity_ = 0;
    rhs.next_ = 0;
    return *this;
  }

  bool push_front(const T &v) override { return insert(0, v); };

  bool push_back(const T &v) override {
    if (next_ >= capacity_) {
      // No free space to add one more element. Need to increase memory
      resize_memory((size_t)(capacity_ * resize_scale_));
    }
    data_[next_] = v;
    next_++;
    return true;
  };

  bool insert(const size_t pos, const T &v) override {
    if (pos >= next_) {
      // invalid position
      return false;
    }
    // processing the end of array
    if (next_ >= capacity_) {
      // No free space to add one more element. Need to increase memory
      resize_memory((size_t)(capacity_ * resize_scale_));
    }
    // need to move all element after 'pos' to one position to the right
    for (int i = next_, j = next_ - 1; j >= static_cast<int>(pos); i--, j--) {
      data_[i] = data_[j];
    }
    data_[pos] = v;
    next_++;
    return true;
  };

  bool erase(const size_t pos) override {
    if (pos >= next_) {
      // invalid position
      return false;
    }
    // need to move all element after 'pos' to one position to the left
    for (size_t i = pos, j = pos + 1; j < next_; ++i, ++j) {
      data_[i] = data_[j];
    }
    next_--;

    if (next_ < (size_t)(capacity_ / resize_scale_)) {
      // Too much free space. Need to reduce memory
      resize_memory((size_t)(capacity_ / resize_scale_));
    }

    return true;
  };

  size_t size() const override { return next_; };

  const T &operator[](const size_t pos) override {
    if (pos >= next_) {
      std::cout << "\nDynamicContainer::operator[]: Array index out of bound, "
                   "exiting";
      std::exit(0);
    }
    return data_[pos];
  };

  VectorIterator<T> begin() { return VectorIterator(&data_[0]); }
  VectorIterator<T> end() { return VectorIterator(&data_[next_]); }

private:
  void resize_memory(size_t new_size) {
    //    std::cout << "\nDynamicContainer::resize_memory: new_size=" <<
    //    new_size
    //              << std::endl;
    T *new_data = new T[new_size];
    for (size_t i = 0; i < next_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    new_data = nullptr;
    capacity_ = new_size;
  };

private:
  T *data_;
  size_t capacity_;
  size_t next_;
  float resize_scale_;
};
