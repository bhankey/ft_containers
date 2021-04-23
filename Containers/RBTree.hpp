//
// Created by sergey on 22.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_RBTREE_HPP_
#define FT_CONTAINERS_CONTAINERS_RBTREE_HPP_

#include "RBTreeNode.hpp"
#include "RBTreeIterator.hpp"
#include "ReverseIterator.hpp"

namespace ft {

template<typename Key, typename MappedType, typename Value, typename Compare, typename Allocator = std::allocator<Pair> >
class RBTree {
 protected:
  typedef RB_tree_node_base* Base_ptr;
  typedef const RB_tree_node_base Const_base_ptr;
  typedef RB_tree_node<Value> Node_ptr;
  typedef const RB_tree_node<Value> Const_node_ptr;
  typedef typename Allocator::template rebind<Node_ptr>::other Node_allocator; // TODO May be problem cus of typedef
 public:
  typedef Key key_type;
  typedef MappedType mapped_type;
  typedef Value value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Allocator allocator_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef TreeIterator<RB_tree_node_base> iterator;
  typedef ConstTreeIterator<RB_tree_node_base> const_iterator;
  typedef ReverseIterator<TreeIterator<RB_tree_node_base> > reverse_iterator;
  typedef ReverseIterator<ConstTreeIterator<RB_tree_node_base> > const_reverse_iterator;
 protected:
  Compare compare_;
  Node_allocator node_allocator_;
  Allocator allocator_;
  size_type size_;
  Node_ptr root_;
  Node_ptr first_;
  Node_ptr last_;
 public:
  RBTree();
  explicit RBTree(const Compare &comp, const Allocator& alloc = Allocator());
  template<typename InputIt>
  RBTree(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator  &allocator = Allocator());
  RBTree(const RBTree &other);
  ~RBTree();
  RBTree &operator=(const RBTree &other);

  // Capacity
  bool empty() const {
    return !size_;
  }
  size_type size() const {
    return size_;
  }
  size_type max_size() const {
    return node_allocator_.max_size();
  }

  // Modifiers
  void clear();

  std::pair(iterator, bool) insert_unique(const Value &value);
  iterator insert_unique(iterator hint, const Value *value);
  template<typename InputIt>
  void insert_unique(InputIt first, InputIt last);

  void erase(iterator pos);
  void erase(iterator first, iterator last);
  size_type erase(const key_type &key);
  void swap(RBTree &other);

  // Lookup
  size_type count(const Key &key) const;
  iterator find(const Key &key) const;
  const_iterator find(const Key &key) const;

  // Observers
  Compare &key_comp() const;

};
}
#endif //FT_CONTAINERS_CONTAINERS_RBTREE_HPP_
