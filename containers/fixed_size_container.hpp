#pragma once
#include "base_container.h"
#include "vector_iterator.hpp"
#include <cstddef>
#include <iostream>

template <typename T, size_t N = 10>
class FixedSizeContainer : public BaseContainer<T> {
public:
  FixedSizeContainer() : size_{N}, next_{0} {};

  bool push_front(const T &v) override { return insert(0, v); };

  bool push_back(const T &v) override {
    if (next_ >= size_) {
      // No free space to add one more element
      return false;
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
    if (next_ < size_) {
      data_[next_] = data_[next_ - 1];
    }
    // need to move all element after 'pos' to one position to the right
    for (int i = next_ - 1, j = next_ - 2; j >= static_cast<int>(pos);
         i--, j--) {
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
    return true;
  };

  size_t size() const override { return next_; };

  const T &operator[](const size_t pos) override {
    if (pos >= next_) {
      std::cout << "\nFixedSizeContainer::operator[]: Array index out of "
                   "bound, exiting";
      std::exit(0);
    }
    return data_[pos];
  };

  VectorIterator<T> begin() { return VectorIterator(&data_[0]); }
  VectorIterator<T> end() { return VectorIterator(&data_[next_]); }

private:
  T data_[N];
  size_t size_;
  size_t next_;
};
