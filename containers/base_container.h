#pragma once
#include "base_iterator.h"
#include <cstddef>

template <typename T> class BaseContainer {
public:
  virtual ~BaseContainer() = default;
  virtual bool push_front(const T &v) = 0;
  virtual bool push_back(const T &v) = 0;
  virtual bool insert(const size_t pos, const T &v) = 0;
  virtual bool erase(const size_t pos) = 0;
  virtual size_t size() const = 0;
  virtual const T &operator[](const size_t pos) = 0;
  //  virtual BaseIterator<T> begin() = 0;
  //  virtual BaseIterator<T> end() = 0;
};
