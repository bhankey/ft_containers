//
// Created by sergey on 22.04.2021.
//

#ifndef FT_CONTAINERS_ITERATORS_RBTREEITERATOR_HPP_
#define FT_CONTAINERS_ITERATORS_RBTREEITERATOR_HPP_

#include "RBTreeNode.hpp"

namespace ft {

template<typename Type>
class TreeIterator {
 public:
  typedef TreeIterator<Type> _Self;
  typedef RB_tree_node<Type> *Node_ptr;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef Type &reference;
  typedef Type *pointer;

  Node_ptr Node;

  TreeIterator(): Node() {
  }
  TreeIterator(const TreeIterator &it): Node(it.Node) {
  }
  ~TreeIterator() {
  }
  TreeIterator &operator=(const _Self &it) {
    Node = it.Node;
    return *this;
  }
  explicit TreeIterator(Node_ptr x): Node(x) {
  };
  reference operator*() const {
    return Node->data;
  }
  pointer operator->() const {
    return &Node->data;
  }
  _Self &operator++() {
    increment();
    return *this;
  }
  _Self operator++(int) {
    _Self tmp = *this;
    increment();
    return tmp;
  }
  _Self &operator--() {
    decrement();
    return *this;
  }
  _Self operator--(int) {
    _Self tmp = *this;
    decrement();
    return tmp;
  }
  bool operator==(const _Self &it) const {
    return Node == it.Node;
  }
  bool operator!=(const _Self &it) const {
    return Node != it.Node;
  }
 protected:
  void increment() {
    if (Node->right != NULL) {
      Node = Node->right;
      while (Node->left != NULL) {
        Node = Node->left;
      }
    }
    else {
      Node_ptr y = Node->parent;
      while (Node == y->right) {
        Node = y;
        y = y->parent;
      }
      if (Node->right != y) {
        Node = y;
      }
    }
  }
  void decrement() {
    if (Node->color == red && Node->parent->parent == Node) {
      Node = Node->right;
    }
    else if (Node->left != NULL) {
      Node_ptr y  = Node->left;
      while (y->right != NULL) {
        y = y->right;
      }
      Node = y;
    }
    else {
      Node_ptr y = Node->parent;
      while (Node == y->left) {
        Node = y;
        y = y->parent;
      }
      Node = y;
    }
  }
};

template<typename Type>
class ConstTreeIterator {
 public:
  typedef ConstTreeIterator<Type> _Self;
  typedef const RB_tree_node<Type> *Node_ptr;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const Type &reference;
  typedef const Type *pointer;

  Node_ptr Node;

  ConstTreeIterator(): Node() {
  }
  ConstTreeIterator(const TreeIterator<Type> &it): Node(it.Node) {
  }
  ~ConstTreeIterator() {
  }
  ConstTreeIterator &operator=(const _Self &it) {
    Node = it.Node;
    return *this;
  }
  explicit ConstTreeIterator(Node_ptr x): Node(x) {
  }
  reference operator*() const {
    return Node->data;
  }
  pointer operator->() const {
    return &Node->data;
  }
  _Self &operator++() {
    increment();
    return *this;
  }
  _Self operator++(int) {
    _Self tmp = *this;
    increment();
    return tmp;
  }
  _Self &operator--() {
    decrement();
    return *this;
  }
  _Self operator--(int) {
    _Self tmp = *this;
    decrement();
    return tmp;
  }
  bool operator==(const _Self &it) const {
    return Node == it.Node;
  }
  bool operator!=(const _Self &it) const {
    return Node != it.Node;
  }
 protected:
  void increment() {
    if (Node->right != NULL) {
      Node = Node->right;
      while (Node->left != NULL) {
        Node = Node->left;
      }
    }
    else {
      Node_ptr y = Node->parent;
      while (Node == y->right) {
        Node = y;
        y = y->parent;
      }
      if (Node->right != y) {
        Node = y;
      }
    }
  }
  void decrement() {
    if (Node->color == red && Node->parent->parent == Node) {
      Node = Node->right;
    }
    else if (Node->left != NULL) {
      Node_ptr y  = Node->left;
      while (y->right != NULL) {
        y = y->right;
      }
      Node = y;
    }
    else {
      Node_ptr y = Node->parent;
      while (Node == y->left) {
        Node = y;
        y = y->parent;
      }
      Node = y;
    }
  }
};

template<typename T>
inline bool operator==(const TreeIterator<T> &lhs, const ConstTreeIterator<T> &rhs) {
  return lhs.Node == rhs.Node;
}

template<typename T>
inline bool operator!=(const TreeIterator<T> &lhs, const ConstTreeIterator<T> &rhs) {
  return lhs.Node != rhs.Node;
}

}

#endif //FT_CONTAINERS_ITERATORS_RBTREEITERATOR_HPP_
