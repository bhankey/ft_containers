//
// Created by sergey on 28.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_QUEUE_HPP_
#define FT_CONTAINERS_CONTAINERS_QUEUE_HPP_

namespace ft {

#include "List.hpp"

template<typename T, typename Container = ft::List<T> >
class Queue {
 protected:
  Container container_;
 public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;

  explicit Queue(const Container &cont = Container()): container_(cont) {
  }
  Queue(const Queue &other): container_(other.container_) {
  }
  Queue &operator=(const Queue &other) {
    if (this != &other) {
      container_ = other.container_;
    }
    return *this;
  }
  ~Queue() {
  }

  value_type &front() {
    return container_.front();
  }
  const value_type &front() const {
    return container_.front();
  }
  value_type &back() {
    return container_.back();
  }
  const value_type &back() const {
    return container_.back();
  }
  bool empty() const {
    return container_.empty();
  }
  size_type size() const {
    return container_.size();
  }
  void push(const value_type &value) {
    container_.push_back(value);
  }
  void pop() {
    container_.pop_front();
  }
  template<typename T_, typename Container_>
  friend bool operator==(const Queue<T_, Container_> &lhs, const Queue<T_, Container_> &rhs);
  template<typename T_, typename Container_>
  friend bool operator<(const Queue<T_, Container_> &lhs, const Queue<T_, Container_> &rhs);
};

template<typename T, typename Container>
bool operator==(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return lhs.container_ == rhs.container_;
}

template<typename T, typename Container>
bool operator!=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return !(lhs == rhs);
}

template<typename T, typename Container>
bool operator<(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return lhs < rhs;
}

template<typename T, typename Container>
bool operator>(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return rhs < lhs;
}

template<typename T, typename Container>
bool operator<=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return !(rhs < lhs);
}

template<typename T, typename Container>
bool operator>=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return !(lhs < rhs);
}
}
#endif //FT_CONTAINERS_CONTAINERS_QUEUE_HPP_
