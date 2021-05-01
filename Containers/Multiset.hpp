//
// Created by sergey on 01.05.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_MULTISET_HPP_
#define FT_CONTAINERS_CONTAINERS_MULTISET_HPP_

#include "RBTreeNode.hpp"
#include "RBTree.hpp"

namespace ft {

template<typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> >
class Multiset {
 public:
  typedef Key key_type;
  typedef Key value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Allocator allocator_type;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
 private:
  typedef RBTree<Key, Key, Identity<value_type>, Compare, Allocator> data_structure;
  data_structure rb_tree_;

  Compare compare_;
 public:
  typedef typename data_structure::iterator iterator;
  typedef typename data_structure::const_iterator const_iterator;
  typedef typename data_structure::reverse_iterator reverse_iterator;
  typedef typename data_structure::const_reverse_iterator const_reverse_iterator;

  // Constructors and destructors
  explicit Multiset(const key_compare &comp = key_compare(),
                    const allocator_type &allocator = allocator_type()) : rb_tree_(comp, allocator),
                                                                          compare_(comp) {
  }
  template<typename InputIt>
  Multiset(InputIt first,
           InputIt last,
           const key_compare &comp = key_compare(),
           const allocator_type &allocator = allocator_type()): rb_tree_(comp, allocator) {
    while (first != last) {
      rb_tree_.insert_equal(*first);
      ++first;
    }
  }
  Multiset(const Multiset &other) : rb_tree_(other.rb_tree_), compare_(other.compare_) {

  }
  Multiset &operator=(const Multiset &other) {
    if (this != &other) {
      rb_tree_ = other.rb_tree_;
    }
    return *this;
  }
  ~Multiset() {
  }

// Iterators
  iterator begin() {
    return rb_tree_.begin();
  }
  const_iterator begin() const {
    return rb_tree_.begin();
  }
  iterator end() {
    return rb_tree_.end();
  }
  const_iterator end() const {
    return rb_tree_.end();
  }
  reverse_iterator rbegin() {
    return rb_tree_.rbegin();
  };
  const_reverse_iterator rbegin() const {
    return rb_tree_.rbegin();
  }
  reverse_iterator rend() {
    return rb_tree_.rend();
  }
  const_reverse_iterator rend() const {
    return rb_tree_.rend();
  }

  // Capacity
  bool empty() const {
    return rb_tree_.empty();
  }
  size_type size() const {
    return rb_tree_.size();
  }
  size_type max_size() const {
    return rb_tree_.max_size();
  }

  // Modifiers
  void clear() {
    rb_tree_.clear();
  }
  iterator insert(const value_type &value) {
    return rb_tree_.insert_equal(value);
  }
  iterator insert(iterator hint, const value_type &value) {
    static_cast<void>(hint);
    return rb_tree_.insert_equal(value);
  }
  template<typename InputIt>
  void insert(InputIt first, InputIt last) {
    while (first != last) {
      rb_tree_.insert_equal(*first);
      ++first;
    }
  }
  void erase(iterator pos) {
    rb_tree_.erase(pos);
  }
  void erase(iterator first, iterator last) {
    rb_tree_.erase(first, last);
  }
  size_type erase(const key_type &key) {
    return rb_tree_.erase(key);
  }
  void swap(Multiset &other) {
    ft::swap(rb_tree_, other.rb_tree_);
    ft::swap(compare_, other.compare_);
  }

  // Operations
  size_type count(const Key &key) const {
    return rb_tree_.count(key);
  }
  iterator find(const Key &key) {
    return rb_tree_.find(key);
  }
  const_iterator find(const Key &key) const {
    return rb_tree_.find(key);
  }
  std::pair<iterator, iterator> equal_range(const Key &key) {
    return rb_tree_.equal_range(key);
  }
  std::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
    return rb_tree_.equal_range(key);
  }
  iterator lower_bound(const Key &key) {
    return rb_tree_.lower_bound(key);
  }
  const_iterator lower_bound(const Key &key) const {
    return rb_tree_.lower_bound(key);
  }
  iterator upper_bound(const Key &key) {
    return rb_tree_.upper_bound(key);
  }
  const_iterator upper_bound(const Key &key) const {
    return rb_tree_.upper_bound(key);
  }
  key_compare key_comp() const {
    return rb_tree_.key_comp();
  }
  value_compare value_comp() const {
    return rb_tree_.key_comp();
  }
};

template<class Key, class Compare, class Alloc>
bool operator==(const Multiset<Key, Compare, Alloc> &lhs,
                const Multiset<Key, Compare, Alloc> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  typename ft::Multiset<Key, Compare, Alloc>::const_iterator lit = lhs.begin(), rit = rhs.begin();
  for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit) {
    if (*lit != *rit) {
      return false;
    }
  }
  if (lit != lhs.end() || rit != rhs.end()) {
    return false;
  }
  return true;
}

template<class Key, class Compare, class Alloc>
bool operator!=(const Multiset<Key, Compare, Alloc> &lhs,
                const Multiset<Key, Compare, Alloc> &rhs) {
  return !(lhs == rhs);
}
template<class Key, class Compare, class Alloc>
bool operator<(const Multiset<Key, Compare, Alloc> &lhs, const Multiset<Key, Compare, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template<class Key, class Compare, class Alloc>
bool operator<=(const Multiset<Key, Compare, Alloc> &lhs,
                const Multiset<Key, Compare, Alloc> &rhs) {
  return !(rhs < lhs);
}
template<class Key, class Compare, class Alloc>
bool operator>(const Multiset<Key, Compare, Alloc> &lhs, const Multiset<Key, Compare, Alloc> &rhs) {
  return rhs < lhs;
}
template<class Key, class Compare, class Alloc>
bool operator>=(const Multiset<Key, Compare, Alloc> &lhs,
                const Multiset<Key, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template<class Key, class Compare, class Alloc>
void swap(Multiset<Key, Compare, Alloc> &lhs, Multiset<Key, Compare, Alloc> &rhs) {
  lhs.swap(rhs);
}
}
#endif //FT_CONTAINERS_CONTAINERS_MULTISET_HPP_
