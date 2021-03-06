//
// Created by sergey on 22.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_RBTREE_HPP_
#define FT_CONTAINERS_CONTAINERS_RBTREE_HPP_

#include "RBTreeNode.hpp"
#include "RBTreeIterator.hpp"
#include "ReverseIterator.hpp"
#include <utility>

namespace ft {

// Inspire by gcc libstdc++ implementation and "Introduction to algorithms" H. Cormen

template<typename Key, typename Value, typename GetKey, typename Compare = std::less<Key>, typename Allocator = std::allocator<Value> >
class RBTree {
 protected:
  typedef RB_tree_node<Value> *Node_ptr;
  typedef const RB_tree_node<Value> Const_node_ptr;
  typedef typename Allocator::template rebind<RB_tree_node<Value> >::other Node_allocator;
 public:
  typedef Key key_type;
  typedef Value value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Allocator allocator_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef TreeIterator<Value> iterator;
  typedef ConstTreeIterator<Value> const_iterator;
  typedef ReverseIterator<TreeIterator<Value> > reverse_iterator;
  typedef ReverseIterator<ConstTreeIterator<Value> > const_reverse_iterator;
 protected:
  Compare compare_;
  Node_allocator node_allocator_;
  Allocator allocator_;
  size_type size_;
  GetKey get_key_;
  Node_ptr header_;

  Node_ptr create_node(const Value &value) {
    Node_ptr ptr = node_allocator_.allocate(1);
    allocator_.construct(&(ptr->data), value);
    ptr->color = red;
    ptr->left = NULL;
    ptr->right = NULL;
    ++size_;
    return ptr;
  }
  void destroy_node(Node_ptr node) {
    allocator_.destroy(&(node->data));
    node_allocator_.deallocate(node, 1);
    --size_;
  }
  Node_ptr &get_header() {
    return header_;
  };

  Node_ptr &get_root() const {
    return header_->parent;
  }
  Node_ptr &get_leftmost() const {
    return header_->left;
  }
  Node_ptr &get_rightmost() const {
    return header_->right;
  }
  void empty_init_tree() {
    header_ = node_allocator_.allocate(1);
    header_->color = red;
    get_root() = NULL;
    get_leftmost() = header_;
    get_rightmost() = header_;
    size_ = 0;
  }


 public:
  RBTree(): compare_(), node_allocator_(), allocator_(), size_(0), get_key_() {
    empty_init_tree();
  }
  explicit RBTree(const Compare &comp, const Allocator& alloc = Allocator()): compare_(comp), node_allocator_(), allocator_(alloc), size_(0), get_key_() {
    empty_init_tree();
  }
  RBTree(const RBTree &other): compare_(other.compare_), node_allocator_(other.node_allocator_), allocator_(other.allocator_), get_key_(other.get_key_) {
    empty_init_tree();
    for (RBTree::const_iterator it = other.begin(); it != other.end(); ++it) {
      insert_equal(*it);
    }
  }
  ~RBTree() {
    clear();
    node_allocator_.deallocate(header_, 1);
  }
  RBTree &operator=(const RBTree &other) {
    if (this != &other) {
      clear();
      compare_ = other.compare_;
      get_key_ = other.get_key_;
      for (RBTree::const_iterator it = other.begin(); it != other.end(); ++it) {
        insert_equal(*it);
      }
    }
    return *this;
  }

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
  void clear() {
    remove_subtree(header_->parent);
    header_->parent = NULL;
    header_->left = header_;
    header_->right = header_;
  }
  std::pair<iterator, bool> insert_unique(const Value &value) {
    Node_ptr  y = get_header();
    Node_ptr x = get_root();
    bool comp = true;
    while (x != 0) {
      y = x;
      comp = compare_(get_key_(value), get_key_(x->data));
      if (comp) {
        x = x->left;
      }
      else {
        x = x->right;
      }
    }
    iterator j = iterator(y);
    if (comp) {
      if (j == begin()) {
        return std::pair<iterator, bool>(insert_node(x, y, value), true) ;
      }
      else
        --j;
    }
    if (compare_(get_key_(j.Node->data), get_key_(value))) {
      return std::pair<iterator, bool>(insert_node(x, y, value), true);
    }
    return std::pair<iterator, bool>(j, false);
  }
  iterator insert_equal(const Value &value) {
    Node_ptr y = get_header();
    Node_ptr x = get_root();
    while (x != 0) {
      y = x;
      if (compare_(get_key_(value), get_key_(x->data))) {
        x = x->left;
      }
      else {
        x = x->right;
      }
    }
    return insert_node(x, y, value);
  }
  void erase(iterator pos) {
    Node_ptr ptr = pos.Node;
    ptr = delete_node(ptr);
    destroy_node(ptr);
  }
  void erase(iterator first, iterator last) {
    while (first != last) {
      erase(first++);
    }
  }
  size_type erase(const key_type &key) {
    std::pair<iterator, iterator> range = equal_range(key);
    size_type  range_size = ft::distance(range.first, range.second);
    erase(range.first, range.second);
    return range_size;
  }
  void swap(RBTree &other) {
    ft::swap(compare_, other.compare_);
    ft::swap(node_allocator_, other.node_allocator_);
    ft::swap(allocator_, other.allocator_);
    ft::swap(size_, other.size_);
    ft::swap(header_, other.header_);
  }

  // Lookup
  size_type count(const Key &key) const {
    std::pair<const_iterator, const_iterator> range = equal_range(key);
    return ft::distance(range.first, range.second);
  }
  iterator find(const Key &key) {
    iterator res = lower_bound(key);
    if (compare_(key, get_key_(res.Node->data))) {
      return end();
    }
    else {
      return res;
    }
  }
  const_iterator find(const Key &key) const {
    const_iterator res = lower_bound(key);
    if (compare_(key, get_key_(res.Node->data))) {
      return end();
    }
    else {
      return res;
    }
  }
  std::pair<iterator,iterator> equal_range(const Key &key) {
    return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
  }
  std::pair<const_iterator,const_iterator> equal_range(const Key &key) const {
    return std::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
  }
  iterator lower_bound(const Key &key) {
    Node_ptr x = get_root();
    Node_ptr res = get_header();
    while (x != NULL) {
      if (!compare_(get_key_(x->data), key)) {
        res = x;
        x = x->left;
      }
      else {
        x = x->right;
      }
    }
    return iterator(res);
  }
  const_iterator lower_bound(const Key &key) const {
    Node_ptr x = get_root();
    Node_ptr res = header_;
    while (x != NULL) {
      if (!compare_(get_key_(x->data), key)) {
        res = x;
        x = x->left;
      }
      else {
        x = x->right;
      }
    }
    return const_iterator(res);
  }
  iterator upper_bound(const Key &key) {
    Node_ptr x = get_root();
    Node_ptr res = get_header();
    while (x != NULL) {
      if (compare_(key, get_key_(x->data))) {
        res = x;
        x = x->left;
      }
      else {
        x = x->right;
      }
    }
    return iterator(res);
  }
  const_iterator upper_bound(const Key &key) const {
    Node_ptr x = get_root();
    Node_ptr res = header_;
    while (x != NULL) {
      if (compare_(key, get_key_(x->data))) {
        res = x;
        x = x->left;
      }
      else {
        x = x->right;
      }
    }
    return const_iterator(res);
  }

  // Iterators
  iterator begin() {
   return iterator(get_leftmost());
  }
  const_iterator begin() const {
   return const_iterator(get_leftmost());
  }
  iterator end() {
   return iterator(header_);
  }
  const_iterator end() const {
    return const_iterator(header_);
  }
  reverse_iterator rbegin() {
    return reverse_iterator(end());
  };
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() {
    return reverse_iterator(begin());
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // Observers
  Compare &key_comp() const {
    return compare_;
  }
 protected:
  Node_ptr minimum(Node_ptr x) {
    while (x->left != NULL) {
      x = x->left;
    }
    return x;
  }
  Node_ptr maximum(Node_ptr x) {
    while (x->right != NULL) {
      x = x->right;
    }
    return x;
  }
  void left_rotate(Node_ptr x) {
    Node_ptr y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x == get_root()) {
      get_root() = y;
    }
    else if (x == x->parent->left) {
      x->parent->left = y;
    }
    else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }
  void right_rotate(Node_ptr x) {
    Node_ptr y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x == get_root()) {
      get_root() = y;
    }
    else if (x == x->parent->right) {
      x->parent->right = y;
    }
    else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }
  iterator insert_node(Node_ptr x, Node_ptr y, const Value &value) {
    Node_ptr z = create_node(value);
    if (y == get_header() || x != 0 || compare_(get_key_(value), get_key_(y->data))) {
      y->left = z;
      if (y == get_header()) {
        get_root() = z;
        get_rightmost() = z;
      }
      else if (y == get_leftmost()) {
        get_leftmost() = z;
      }
    }
    else {
      y->right = z;
      if (y == get_rightmost()) {
        get_rightmost() = z;
      }
    }
    z->parent = y;
    z->left = NULL;
    z->right = NULL;
    insert_fixup(z);
    return (iterator(z));
  }
  void insert_fixup(Node_ptr z) {
    z->color = red;
    while (z != get_root() && z->parent->color == red) {
      if (z->parent == z->parent->parent->left) {
        Node_ptr y = z->parent->parent->right;
        if (y != NULL && y->color == red) {
          z->parent->color = black;
          y->color = black;
          z->parent->parent->color = red;
          z = z->parent->parent;
        }
        else {
          if (z == z->parent->right) {
          z = z->parent;
          left_rotate(z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        right_rotate(z->parent->parent);
        }
      }
      else {
        Node_ptr y = z->parent->parent->left;
        if (y != NULL && y->color == red) {
          z->parent->color = black;
          y->color = black;
          z->parent->parent->color = red;
          z = z->parent->parent;
        }
        else {
          if (z == z->parent->left) {
            z = z->parent;
            right_rotate(z);
          }
          z->parent->color = black;
          z->parent->parent->color = red;
          left_rotate(z->parent->parent);
        }
      }
    }
    get_root()->color = black;
  }
  Node_ptr delete_node(Node_ptr z) {
    Node_ptr &root = get_root();
    Node_ptr &left_most = get_leftmost();
    Node_ptr &right_most = get_rightmost();
    Node_ptr y = z;
    Node_ptr x = NULL;
    Node_ptr x_parent = NULL;
    if (y->left == NULL) {
      x = y->right;
    }
    else {
      if (y->right == NULL) {
        x = y->left;
      }
      else {
        y = y->right;
        while (y->left != NULL) {
          y = y->left;
        }
        x = y->right;
      }
    }
    if (y != z) {
      z->left->parent = y;
      y->left = z->left;
      if (y != z->right) {
        x_parent = y->parent;
        if (x) {
          x->parent = y->parent;
        }
        y->parent->left = x;
        y->right = z->right;
        z->right->parent = y;
      }
      else {
        x_parent = y;
      }
      if (root == z) {
        root = y;
      }
      else if (z->parent->left == z) {
        z->parent->left = y;
      }
      else {
        z->parent->right = y;
      }
      y->parent = z->parent;
      ft::swap(y->color, z->color);
      y = z;
    }
    else {
      x_parent = y->parent;
      if (x != NULL) {
        x->parent = y->parent;
      }
      if (root == z) {
        root = x;
      }
      else {
        if (z->parent->left == z) {
          z->parent->left = x;
        }
        else {
          z->parent->right = x;
        }
      }
      if (left_most == z) {
        if (z->right == NULL) {
          left_most = z->parent;
        }
        else {
          left_most = minimum(x);
        }
      }
      if (right_most == z) {
        if (z->left == NULL) {
          right_most = z->parent;
        }
        else {
          right_most = maximum(x);
        }
      }
    }
    if (y->color == black) {
      while (x != root && (x == NULL || x->color == black)) {
        if (x == x_parent->left) {
          Node_ptr  w = x_parent->right;
          if (w->color == red) {
            w->color = black;
            x_parent->color = red;
            left_rotate(x_parent);
            w = x_parent->right;
          }
          if ((w->left == NULL || w->left->color == black) && (w->right == NULL || w->right->color == black)) {
            w->color = red;
            x = x_parent;
            x_parent = x_parent->parent;
          }
          else {
            if (w->right == NULL || w->right->color == black) {
              if (w->left != NULL) {
                w->left->color = black;
              }
              w->color = red;
              right_rotate(w);
              w = x_parent->right;
            }
            w->color = x_parent->color;
            x_parent->color = black;
            if (w->right != NULL) {
              w->right->color = black;
            }
            left_rotate(x_parent);
            break;
          }
        }
        else {
          Node_ptr w = x_parent->left;
          if (w->color == red) {
            w->color = black;
            x_parent->color = red;
            right_rotate(x_parent);
            w = x_parent->left;
          }
          if ((w->right == NULL || w->right->color == black) && (w->left == NULL || w->left->color == black)) {
            w->color = red;
            x = x_parent;
            x_parent = x_parent->parent;
          }
          else {
            if (w->left == NULL || w->left->color == black) {
              if (w->right != NULL) {
                w->right->color = black;
              }
              w->color = red;
              left_rotate(w);
              w = x_parent->left;
            }
            w->color = x_parent->color;
            x_parent->color = black;
            if (w->left != NULL) {
              w->left->color = black;
            }
            right_rotate(x_parent);
            break;
          }
        }
      }
      if (x != NULL) {
        x->color = black;
      }
    }
    return y;
  }
  void remove_subtree(Node_ptr node) {
    if (node != NULL) {
      remove_subtree(node->left);
      remove_subtree(node->right);
      destroy_node(node);
    }
  }
};

}
#endif //FT_CONTAINERS_CONTAINERS_RBTREE_HPP_
