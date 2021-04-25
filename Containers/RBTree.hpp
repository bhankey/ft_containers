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

template<typename Key, typename MappedType, typename Value, typename Compare = std::less<Key>, typename Allocator = std::allocator<Value> >
class RBTree {
 protected:
  typedef RB_tree_node<Value> *Node_ptr;
  typedef const RB_tree_node<Value> Const_node_ptr;
  typedef typename Allocator::template rebind<RB_tree_node<Value> >::other Node_allocator; // TODO May be problem cus of typedef
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
  typedef TreeIterator<Value> iterator;
  typedef ConstTreeIterator<Value> const_iterator;
  typedef ReverseIterator<TreeIterator<Value> > reverse_iterator;
  typedef ReverseIterator<ConstTreeIterator<Value> > const_reverse_iterator;
 protected:
  Compare compare_;
  Node_allocator node_allocator_;
  Allocator allocator_;
  size_type size_;

  Node_ptr root_;
  RB_tree_node<Value> header_;

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

 public:
  RBTree(): compare_(), node_allocator_(), allocator_(), size_(0), root_(NULL) {
    header_.color = black;
  }
  explicit RBTree(const Compare &comp, const Allocator& alloc = Allocator()): compare_(comp), node_allocator_(), allocator_(alloc), size_(0),  root_(NULL) {
    header_.color = black;
  }
  template<typename InputIt>
  RBTree(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator  &allocator = Allocator()): compare_(comp), node_allocator_(), allocator_(allocator), size_(0), root_(NULL) {
    header_.color = black;
    insert_unique(first, last);
  }
  RBTree(const RBTree &other): compare_(other.compare_), node_allocator_(other.node_allocator_), allocator_(other.allocator_) {
    if (other.root_ == NULL) {
      header_.color = black;
    }
    else {
      operator=(other);
    }
  }
  ~RBTree() {
    clear();
  }
  RBTree &operator=(const RBTree &other) {
    if (this != &other) {
      clear();
      insert_unique(other.begin(), other.end());
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
    remove_subtree(root_);
    root_ = NULL;
  }

  std::pair<iterator, bool> insert_unique(const Value &value) {
    // TODO normal !!!
    Node_ptr ptr = create_node(value);
    insert_node(ptr);
    return std::pair<iterator, bool>();
  }
  iterator insert_unique(iterator hint, const Value *value) {
    static_cast<void>(hint);
    insert_unique(value);
  }
  template<typename InputIt>
  void insert_unique(InputIt first, InputIt last) {
    while (first != last) {
      insert_unique(*first);
      ++first;
    }
  }

  void erase(iterator pos) {
    Node_ptr *ptr = pos.Node;
    delete_node(ptr);
    destroy_node(ptr);
  }
  void erase(iterator first, iterator last) {
    while (first != last) {
      erase(first);
      ++first;
    }
  }
  size_type erase(const key_type &key) {
    Node_ptr ptr = find_node(key);
    if (ptr == NULL) {
      return 0;
    }
    else {
      erase(iterator(ptr));
      return 1;
    }
  }
  void swap(RBTree &other) {
    std::swap(compare_, other.compare_);
    std::swap(node_allocator_, other.node_allocator_);
    std::swap(allocator_, other.allocator_);
    std::swap(size_, other.size_);
    std::swap(root_, other.root_);
    std::swap(header_, other.header_);
  }

  // Lookup
  size_type count(const Key &key) const {
    size_type i = 0;
    const_iterator it = begin();
    while (it != end()) {
      if (it->first == key) { // TODO use comp function
        ++i;
      }
      ++it;
    }
    return i;
  }
  iterator find(const Key &key);
  const_iterator find(const Key &key) const;

  // Iterators
  iterator begin() {
    Node_ptr tmp = minimum(root_);
   return iterator(tmp);
  }
  const_iterator begin() const {
   return const_iterator(minimum(root_));
  }
  iterator end() {
   return iterator(&header_);
  }
  const_iterator end() const {
    return const_iterator(&header_);
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
//  ft::map::value_compare value_comp() const;
 public:
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
    if (x->parent == NULL) {
      root_ = y;
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
    if (x->parent == NULL) {
      root_ = y;
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
  void insert_node(Node_ptr z) {
    Node_ptr y = &header_;
    Node_ptr x = root_;
    while (x != NULL) {
      y = x;
      if (compare_(z->data.first, x->data.first)) {
        x = x->left;
      }
      else {
        x = x->right;
      }
    }
    z->parent = y;
    if (y == NULL || y == &header_) {
      root_ = z;
      root_->parent = &header_;
      header_.parent = root_;
    }
    else if (compare_(z->data.first, y->data.first)) {
      y->left = z;
    }
    else {
      y->right = z;
    }
    z->left = NULL;
    z->right = NULL;
    insert_fixup(z);
  }
  void insert_fixup(Node_ptr z) {
    while (z->parent->color == red) {
      if (z->parent == z->parent->parent->left) {
        Node_ptr y = z->parent->parent->right;
        if (y->color == red) {
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
        if (y->color == red) {
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
    root_->color = black;
  }
  void transplant(Node_ptr u, Node_ptr v) {
    if (u->parent != NULL) {
      root_ = v;
    }
    else if (u == u->parent->left) {
      u->parent->left = v;
    }
    else {
      u->parent->right = v;
    }
    if (v != NULL) {
      v->parent = u->parent;
    }
  }
  void delete_node(Node_ptr z) {
    Node_ptr y = z;
    Node_ptr x;
    enum RB_tree_color y_original_color = y->color;
    if (z->left == NULL) {
      x = z->right;
      transplant(z, z->right);
    }
    else if (z->right == NULL) {
      x = z->left;
      transplant(z, z->left);
    }
    else {
      y == minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      }
      else {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    if (y_original_color == black) {
      delete_node_fixup(x);
    }
  }
  void delete_node_fixup(Node_ptr x) {
    while (x != root_ && x->color == black) {
      if (x == x->parent->left) {
        Node_ptr w = x->parent->right;
        if (w->color == red) {
          w->color = black;
          x->parent->color = red;
          left_rotate(x->parent);
          w = x->parent->right;
        }
        if (w->left->color == black && w->right->color == black) {
          w->color = red;
          x = x->parent;
        }
        else {
          if (w->right->color == black) {
            w->left->color = black;
            w->color = red;
            right_rotate(w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = black;
          w->right->color = black;
          left_rotate(x->parent);
          x = root_;
        }
      }
      else {
        Node_ptr w = x->parent->left;
        if (w->color == red) {
          w->color = black;
          x->parent->color = red;
          right_rotate(x->parent);
          w = x->parent->left;
        }
        if (w->right->color == black && w->left->color == black) {
          w->color = red;
          x = x->parent;
        }
        else {
          if (w->left->color == black) {
            w->right->color = black;
            w->color = red;
            left_rotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = black;
          w->left->color = black;
          right_rotate(x->parent);
          x = root_;
        }
      }
    }
    x->color = black;
  }
  Node_ptr find_node(Key key) {
    Node_ptr node = root_;
    while (node != NULL) {
      if (node->data.first == key) {
        return node;
      }
      else {
        if (compare_(key, node->data.first)) {
          node = node->left;
        }
        else {
          node = node->right;
        }
      }
    }
    return NULL;
  }
  void remove_subtree(Node_ptr node) {
    if (node != NULL) {
      remove_subtree(node->left);
      remove_subtree(node->right);
      destroy_node(node);
    }
    node = NULL;
  }

  void inorder_f(Node_ptr x) {
    if (x != NULL) {
      inorder_f(x->left);
      std::cout << static_cast<Node_ptr>(x)->data.first << " ";
      inorder_f(x->right);
    }
  }
  void inorder() {
    inorder_f(root_);
  }
};
}
#endif //FT_CONTAINERS_CONTAINERS_RBTREE_HPP_
