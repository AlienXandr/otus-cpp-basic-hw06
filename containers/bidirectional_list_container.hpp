#pragma once
#include "base_container.h"
#include "bidirectional_data_node.hpp"
#include "bidirectional_list_iterator.hpp"
#include <cstddef>
#include <iostream>

template <typename T>
class BidirectionalListContainer : public BaseContainer<T> {
public:
  BidirectionalListContainer() = default;
  ~BidirectionalListContainer() override {
    while (head_ != NULL) {
      erase(0);
    }
  };

  bool push_front(const T &v) override { return insert(0, v); };

  bool push_back(const T &v) override { return insert(size_, v); };

  BidirectionalDataNode<T> *get(size_t pos) {
    BidirectionalDataNode<T> *ptr = head_;
    size_t idx = 0;

    while (idx != pos) {
      if (ptr == NULL)
        return ptr;
      ptr = ptr->next_;
      idx++;
    }

    return ptr;
  }

  bool insert(const size_t pos, const T &v) override {
    if (pos > size_) {
      // invalid position
      return false;
    }

    size_++;

    BidirectionalDataNode<T> *node = new BidirectionalDataNode(v);
    BidirectionalDataNode<T> *right = get(pos);

    if (right == NULL) {
      node->prev_ = tail_;
      if (tail_ != NULL) {
        tail_->next_ = node;
      }
      if (head_ == NULL) {
        head_ = node;
      }
      tail_ = node;
      return true;
    }

    BidirectionalDataNode<T> *left = right->prev_;
    if (left == NULL) {
      node->next_ = head_;
      if (head_ != NULL) {
        head_->prev_ = node;
      }
      if (tail_ == NULL) {
        tail_ = node;
      }
      head_ = node;
      return true;
    }

    node->prev_ = left;
    node->next_ = right;
    left->next_ = node;
    right->prev_ = node;

    return true;
  };

  bool erase(const size_t pos) override {
    if (pos >= size_) {
      // invalid position
      return false;
    }

    BidirectionalDataNode<T> *node = get(pos);
    BidirectionalDataNode<T> *left = node->prev_;
    BidirectionalDataNode<T> *right = node->next_;

    if (node == NULL) {
      return false;
    }

    size_--;

    if (left == NULL) {
      // If left == NULL, then I am the head_
      BidirectionalDataNode<T> *ptr = head_->next_;
      if (ptr != NULL) {
        ptr->prev_ = NULL;
      } else {
        tail_ = NULL;
      }
      delete head_;
      head_ = ptr;
      return true;
    }

    if (right == NULL) {
      // If right == NULL, then I am the tail_
      BidirectionalDataNode<T> *ptr = tail_->prev_;
      if (ptr != NULL) {
        ptr->next_ = NULL;
      } else {
        head_ = NULL;
      }

      delete tail_;
      tail_ = ptr;
      return true;
    }

    left->next_ = right;
    right->prev_ = left;

    delete node;
    return true;
  };

  size_t size() const override { return size_; };

  const T &operator[](const size_t pos) override {
    if (pos >= size_) {
      std::cout << "\nBidirectionalListContainer::operator[]: Array index out "
                   "of bound, "
                   "exiting";
      std::exit(0);
    }

    return get(pos)->get_data();
  };

  BidirectionalListIterator<T> begin() {
    return BidirectionalListIterator(head_);
  }
  BidirectionalListIterator<T> end() {
    return BidirectionalListIterator(tail_);
  }

private:
  size_t size_{0};
  BidirectionalDataNode<T> *head_{NULL};
  BidirectionalDataNode<T> *tail_{NULL};
};
