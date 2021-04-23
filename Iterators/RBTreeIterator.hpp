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
  typedef RB_tree_node_base *Base_Node_ptr;
  typedef RB_tree_node<Type> *Node_ptr
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef Type &reference;
  typedef Type *pointer;

  Base_Node_ptr Node;

  TreeIterator();
  TreeIterator(const TreeIterator &it);
  ~TreeIterator();
  TreeIterator &operator=(const _Self &it);
  explicit TreeIterator(Base_Node_ptr x);
  reference operator*() const;
  pointer operator->() const;
  _Self &operator++();
  _Self operator++(int);
  _Self &operator--();
  _Self operator--(int);
  bool operator==(const _Self &it) const;
  bool operator!=(const _Self &it) const;

}

template<typename Type>
class ConstTreeIterator {
 public:
  typedef ConstTreeIterator<Type> _Self;
  typedef const RB_tree_node_base *Base_Node_ptr;
  typedef const RB_tree_node<Type> *Node_ptr
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef Type &reference;
  typedef Type *pointer;

  Base_Node_ptr Node;

  ConstTreeIterator();
  ConstTreeIterator(const TreeIterator &it);
  ~ConstTreeIterator();
  ConstTreeIterator &operator=(const _Self &it);
  explicit TreeIterator(Base_Node_ptr x);
  reference operator*() const;
  pointer operator->() const;
  _Self &operator++();
  _Self operator++(int);
  _Self &operator--();
  _Self operator--(int);
  bool operator==(const _Self &it) const;
  bool operator!=(const _Self &it) const;

}

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
