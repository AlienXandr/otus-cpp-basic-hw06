#pragma once
#include <cstdlib>

template <typename T> class BidirectionalDataNode {
public:
  explicit BidirectionalDataNode(const T &v) : data_{v} {}
  T &get_data() { return data_; }

public:
  T data_;
  BidirectionalDataNode<T> *prev_{NULL};
  BidirectionalDataNode<T> *next_{NULL};
};