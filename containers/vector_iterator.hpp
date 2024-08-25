#pragma once

// Iterator for continuous containers
template <typename T> class VectorIterator {
public:
  explicit VectorIterator(T *it) : iterator{it} {}

  T &operator*() const { return *iterator; }

  bool operator!=(const VectorIterator &right) const {
    return iterator != right.iterator;
  }
  VectorIterator operator+(int index) const {
    return VectorIterator(iterator + index);
  }
  VectorIterator operator-(int index) const {
    return VectorIterator(iterator - index);
  }
  VectorIterator &operator++() {
    ++iterator;
    return *this;
  }
  VectorIterator &operator--() {
    --iterator;
    return *this;
  }

private:
  T *iterator;
};