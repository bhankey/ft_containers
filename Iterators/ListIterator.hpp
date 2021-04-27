//
// Created by sergey on 19.04.2021.
//

#ifndef FT_CONTAINERS_ITERATORS_LISTITERATOR_HPP_
#define FT_CONTAINERS_ITERATORS_LISTITERATOR_HPP_

#include "ListNode.hpp"

namespace ft {

template<typename Type>
class ListIterator {
 public:
  typedef ListIterator<Type> _Self;
  typedef List_node<Type> _Node;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef Type *pointer;
  typedef Type &reference;


  List_basic_node *Node;


  ListIterator(): Node() {
  }
  ListIterator(const ListIterator &it): Node(it.Node) {
  }
  ~ListIterator() {
  }
  ListIterator &operator=(const ListIterator &it) {
    Node = it.Node;
    return *this;
  }
  explicit ListIterator(List_basic_node *x): Node(x) {
  }
  reference  operator*() const {
    return static_cast<_Node *>(Node)->data;
  }
  pointer operator->() const {
    return &(static_cast<_Node *>(Node)->data);
  }
  _Self &operator++() {
    Node = Node->next;
    return *this;
  }
  _Self operator++(int) {
    _Self tmp = *this;
    Node = Node->next;
    return tmp;
  }
  _Self &operator--() {
    Node = Node->prev;
    return *this;
  }
  _Self operator--(int) {
    _Self tmp = *this;
    Node = Node->prev;
    return tmp;
  }
  bool operator==(const _Self &it) const {
    return Node == it.Node;
  }
  bool  operator!=(const _Self &it) const {
    return Node != it.Node;
  }
};


template<typename Type>
class ConstListIterator {
 public:
  typedef ConstListIterator<Type> _Self;
  typedef const List_node<Type> _Node;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const Type *pointer;
  typedef const Type &reference;


  const List_basic_node *Node;


  ConstListIterator(): Node() {
  }
  ConstListIterator(const ConstListIterator &it): Node(it.Node) {
  }
  ~ConstListIterator() {
  }
  ConstListIterator &operator=(const ConstListIterator &it) {
    Node = it.Node;
    return *this;
  }
  explicit ConstListIterator(const List_basic_node *x): Node(x) {
  }
  explicit ConstListIterator(const ListIterator<Type> &it): Node(it.Node) {
  }
  reference  operator*() const {
    return static_cast<_Node *>(Node)->data;
  }
  pointer operator->() const {
    return &(static_cast<_Node *>(Node)->data);
  }
  _Self &operator++() {
    Node = Node->next;
    return *this;
  }
  _Self operator++(int) {
    _Self tmp = *this;
    Node = Node->next;
    return tmp;
  }
  _Self &operator--() {
    Node = Node->prev;
    return *this;
  }
  _Self operator--(int) {
    _Self tmp = *this;
    Node = Node->prev;
    return tmp;
  }
  bool operator==(const _Self &it) const {
    return Node == it.Node;
  }
  bool  operator!=(const _Self &it) const {
    return Node != it.Node;
  }
};

template<typename T>
inline bool operator==(const ListIterator<T> &lhs, const ConstListIterator<T> &rhs) {
  return lhs.Node == rhs.Node;
}

template<typename T>
inline bool operator!=(const ListIterator<T> &lhs, const ConstListIterator<T> &rhs) {
  return lhs.Node != rhs.Node;
}

}



#endif //FT_CONTAINERS_ITERATORS_LISTITERATOR_HPP_
