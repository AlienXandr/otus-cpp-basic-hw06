#pragma once

template <typename T> class BaseIterator {
public:
  virtual ~BaseIterator() = default;
  virtual T &operator*() const = 0;
  virtual bool operator!=(const BaseIterator &right) const = 0;
  virtual BaseIterator operator+(int index) const = 0;
  virtual BaseIterator operator-(int index) const = 0;
  virtual BaseIterator &operator++() = 0;
  virtual BaseIterator &operator--() = 0;
};
