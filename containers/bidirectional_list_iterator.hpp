#pragma once
#include "bidirectional_data_node.hpp"

// Iterator for list containers
template <typename T> class BidirectionalListIterator {
public:
  explicit BidirectionalListIterator(BidirectionalDataNode<T> *it)
      : iterator{it} {}

  T &operator*() const { return iterator->get_data(); }

  bool operator!=(const BidirectionalListIterator &right) const {
    return iterator != right.iterator;
  }
  BidirectionalListIterator operator+(int index) const {
    BidirectionalDataNode<T> *ptr = iterator;
    int count = 0;

    while (count < index && ptr != NULL) {
      ptr = ptr->next_;
      count++;
    }

    return BidirectionalListIterator(ptr);
  }
  BidirectionalListIterator operator-(int index) const {
    BidirectionalDataNode<T> *ptr = iterator;
    int count = 0;

    while (count < index && ptr != NULL) {
      ptr = ptr->prev_;
      count++;
    }

    return BidirectionalListIterator(ptr);
  }
  BidirectionalListIterator &operator++() {
    iterator = iterator->next_;
    return *this;
  }
  BidirectionalListIterator &operator--() {
    iterator = iterator->prev_;
    return *this;
  }

private:
  BidirectionalDataNode<T> *iterator;
};