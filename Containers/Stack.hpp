//
// Created by sergey on 28.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_STACK_HPP_
#define FT_CONTAINERS_CONTAINERS_STACK_HPP_

namespace ft {

#include "List.hpp"

template <typename T, typename Container = ft::List<T> >
class Stack {
 protected:
  Container container_;
 public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;

  explicit Stack(const Container &cont = Container()): container_(cont) {
  }
  Stack(const Stack &other): container_(other.container_) {
  }
  Stack &operator=(const Stack &other) {
    if (this != &other) {
      container_ = other.container_;
    }
    return *this;
  }
  ~Stack() {
  }
  bool empty() const {
    return container_.empty();
  }
  size_type size() const {
    return container_.size();
  }
  value_type &top() {
    return container_.back();
  }
  const value_type  &top() const {
    container_.back();
  }
  void push(const value_type &value) {
    container_.push_back(value);
  }
  void pop() {
    container_.pop_back();
  }

  friend bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

  friend bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
};

template<typename T, typename Container>
bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return lhs.container_ == rhs.container_;
}

template<typename T, typename Container>
bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return !(lhs == rhs);
}

template<typename T, typename Container>
bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return lhs < rhs;
}

template<typename T, typename Container>
bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return rhs < lhs;
}

template<typename T, typename Container>
bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return !(rhs < lhs);
}

template<typename T, typename Container>
bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return !(lhs < rhs);
}

}

#endif //FT_CONTAINERS_CONTAINERS_STACK_HPP_
