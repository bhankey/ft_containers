//
// Created by sergey on 19.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_LIST_HPP_
#define FT_CONTAINERS_CONTAINERS_LIST_HPP_

#include "ListIterator.hpp"
#include "ListNode.hpp"

namespace ft {



template<typename T, typename Allocator = std::allocator<T> >
class List {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef ListIterator<T> iterator;
  typedef ConstListIterator<T> const_iterator;
  typedef ReverseIterator<ListIterator<T> > reverse_iterator;
  typedef ReverseIterator<ConstListIterator<T> > const_reverse_iterator;
 protected:
  typedef typename Allocator::template rebind<List_node<T> >::other Node_allocator_;
  typedef List_node<T> _Node;
  typedef List_node<T> *_Node_pointer;
  size_type size_;
  allocator_type allocator_;
  Node_allocator_ node_allocator_;
  List_basic_node node_;

  List_node<T> *create_node(const value_type &x) {
    List_node<T> *ptr = node_allocator_.allocate(1);
    allocator_.construct(&(ptr->data), x);
    ++size_;
    return ptr;
  }
  void destroy_node(List_basic_node *node) {
    _Node_pointer ptr = static_cast<_Node_pointer>(node);
    allocator_.destroy(&(ptr->data));
    node_allocator_.deallocate(ptr, 1);
    --size_;
  }
  void make_connection(List_basic_node *prev, List_basic_node *next) {
    prev->next = next;
    next->prev = prev;
  }
  void make_connection(List_basic_node *prev, List_basic_node *to_insert, List_basic_node *next) {
    make_connection(prev, to_insert);
    make_connection(to_insert, next);
  }
 public:

  // Constructor and destructors
  List() : size_(0), allocator_(Allocator()), node_allocator_(), node_() {
    node_.next = &node_;
    node_.prev = &node_;
  }
  explicit List(const Allocator &alloc) : size_(0), allocator_(alloc), node_allocator_(), node_() {
    node_.next = &node_;
    node_.prev = &node_;
  }
  explicit List(size_type count, const T &value = T(), const Allocator &alloc = Allocator()) :
      size_(0), allocator_(alloc), node_allocator_(), node_() {
    node_.next = &node_;
    node_.prev = &node_;
    List_basic_node *ptr = &node_;
    while (count) {
      List_basic_node *tmp = create_node(value);
      make_connection(ptr, tmp);
      ptr = ptr->next;
      --count;
    }
    make_connection(ptr, &node_);
  }
  template<typename InputIt>
  List(InputIt first, InputIt last, const Allocator &alloc = Allocator())
      : size_(0), allocator_(alloc), node_allocator_(), node_() {
    node_.next = &node_;
    node_.prev = &node_;
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }
  List(const List &other) :
      size_(0), allocator_(other.allocator_), node_allocator_(other.node_allocator_), node_() {
    node_.next = &node_;
    node_.prev = &node_;
    for (const_iterator it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
  }
  ~List() {
    clear();
  }
  List &operator=(const List &other) {
    if (this != &other) {
      clear();
      size_ = 0;
      allocator_ = other.allocator_;
      node_allocator_ = other.node_allocator_;
      for (const_iterator it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
      }
    }
    return *this;
  }

  // Assign
  void assign(size_type count, const T &value) {
    clear();
    while (count) {
      push_back(value);
      --count;
    }
  }
  template<typename InputIt>
  void assign(InputIt first, InputIt last) {
    clear();
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }

  // Element access
  reference front() {
    return static_cast<_Node_pointer>(node_.next)->data;
  }
  const_reference front() const {
    return static_cast<_Node_pointer>(node_.next)->data;
  }
  reference back() {
    return static_cast<_Node_pointer>(node_.prev)->data;
  }
  const_reference back() const {
    return static_cast<_Node_pointer>(node_.prev)->data;
  }

  // Iterators
  iterator begin() {
    return iterator(node_.next);
  }
  const_iterator begin() const {
    return const_iterator(node_.next);
  }
  iterator end() {
    return iterator(&node_);
  }
  const_iterator end() const {
    return const_iterator(&node_);
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

  // Capacity functions
  bool empty() const {
    return size_;
  }
  size_type size() const {
    return size_;
  }
  size_type max_size() const {
    return node_allocator_.max_size();
  }

  // Modifiers
  void clear() {
    List_basic_node *ptr = node_.next;
    while (ptr != &node_) {
      List_basic_node *tmp = ptr->next;
      destroy_node(static_cast<_Node_pointer>(ptr));
      ptr = tmp;
    }
    node_.next = &node_;
    node_.prev = &node_;
  }
  iterator insert(iterator pos, const T &value) {
    List_basic_node *new_node = create_node(value);
    List_basic_node *ptr_pos = pos.Node;
    make_connection(ptr_pos->prev, new_node, ptr_pos);
    return iterator(new_node);
  }
  void insert(iterator pos, size_type count, const T &value) {
    while (count != 0) {
      insert(pos, value);
      --count;
    }
  }
  template<class InputIt>
  void insert(iterator pos, InputIt first, InputIt last) {
    while (first != last) {
      insert(pos, *first);
      ++first;
    }
  }
  iterator erase(iterator pos) {
    List_basic_node *ptr = pos.Node;
    List_basic_node *return_ptr = ptr->next;
    make_connection(ptr->prev, ptr->next);
    destroy_node(ptr);
    return return_ptr;
  }
  iterator erase(iterator first, iterator last) {
    while (first != last) {
      erase(first++);
    }
    return first;
  }
  void push_back(const T &value) {
    List_basic_node *tmp = create_node(value);
    make_connection(node_.prev, tmp, &node_);
  }
  void pop_back() {
    List_basic_node *tmp = node_.prev;
    make_connection(tmp->prev, &node_);
    destroy_node(tmp);
  }
  void push_front(const T &value) {
    List_basic_node *tmp = create_node(value);
    make_connection(&node_, tmp, node_.next);
  }
  void pop_front() {
    List_basic_node *tmp = node_.next;
    make_connection(&node_, tmp->next);
    destroy_node(tmp);
  }
  void resize(size_type count, T value = T()) {
    if (count > size_) {
      while (count > size_) {
        push_back(value);
      }
    } else if (count < size_) {
      while (count < size_) {
        pop_back();
      }
    }
  }
  void swap(List &other) {
    std::swap(size_, other.size_);
    std::swap(allocator_, other.allocator_);
    std::swap(node_allocator_, other.node_allocator_);
    std::swap(node_, other.node_);
  }

  // Operations
  void merge(List &other) {
    merge(other, std::less<value_type>());
  }
  template<class Compare>
  void merge(List &other, Compare comp) {
    if (this != &other) {
      List_basic_node *this_ptr = node_.next;
      List_basic_node *other_ptr = other.node_.next;
      while (this_ptr != &node_ && other_ptr != &other.node_) {
        if (comp(static_cast<_Node_pointer>(this_ptr)->data,
                 static_cast<_Node_pointer>(other_ptr)->data)) {
          this_ptr = this_ptr->next;
        } else {
          make_connection(other_ptr->prev, other_ptr->next);
          List_basic_node *tmp = other_ptr;
          other_ptr = other_ptr->next;
          make_connection(this_ptr->prev, tmp, this_ptr);
          ++size_;
        }
      }
      while (other_ptr != &other.node_) {
        make_connection(other_ptr->prev, other_ptr->next);
        List_basic_node *tmp = other_ptr;
        other_ptr = other_ptr->next;
        make_connection(this_ptr->prev, tmp, this_ptr);
        ++size_;
      }
      other.clear();
    }
  }
  void splice(iterator pos, List &other) {
    splice(pos, other, other.begin(), other.end());
  }
  void splice(iterator pos, List &other, iterator it) {
    List_basic_node *this_ptr = pos.Node;
    List_basic_node *other_ptr = it.Node;
    make_connection(other_ptr->prev, other_ptr->next);
    make_connection(this_ptr->prev, other_ptr, this_ptr);
    --other.size_;
    ++size_;
  }
  void splice(iterator pos, List &other, iterator first, iterator last) {
    List_basic_node *this_ptr = pos.Node;
    List_basic_node *start_ptr = first.Node;
    List_basic_node *finish_ptr = last.Node;
    while (start_ptr != finish_ptr) {
      List_basic_node *tmp = start_ptr;
      make_connection(start_ptr->prev, start_ptr->next);
      start_ptr = start_ptr->next;
      make_connection(this_ptr->prev, tmp, this_ptr);
      --other.size_;
      ++size_;
    }
  }
  void remove(const T &value) {
    for (iterator it = begin(); it != end(); ++it) {
      if (*it == value) {
        it = erase(it);
      } else {
        ++it;
      }
    }
  }
  template<typename UnaryPredicate>
  void remove_if(UnaryPredicate p) {
    for (iterator it = begin(); it != end(); ++it) {
      if (p(*it) == true) {
        it = erase(it);
      } else {
        ++it;
      }
    }
  }
  void reverse() {
    List_basic_node *ptr = node_.next;
    while (ptr != &node_) {
      List_basic_node *tmp = ptr->next;
      std::swap(ptr->next, ptr->prev);
      ptr = tmp;
    }
    std::swap(node_.next, node_.prev);
  }
  void unique() {
    unique(std::equal_to<value_type>());
  }
  template<class BinaryPredicate>
  void unique(BinaryPredicate p) {
    List_basic_node *start = node_.next;
    while (start->next != &node_) {
      if (p(static_cast<_Node_pointer>(start)->data,
            static_cast<_Node_pointer>(start->next)->data)) {
        List_basic_node *tmp = start->next;
        make_connection(start, tmp->next);
        destroy_node(tmp);
      } else {
        start = start->next;
      }
    }
  }
  void sort() {
    sort(std::less<value_type>());
  }
  template<class Compare>
  void sort(Compare comp) {
    if (size_ <= 1) {
      return;
    }
    List<value_type, allocator_type> tmp;
    iterator centre = begin();
    advance(centre, size_ / 2);
    tmp.splice(tmp.begin(), *this, begin(), centre);
    sort(comp);
    tmp.sort(comp);
    merge(tmp, comp);
  }
};
template<class T, class Alloc>
bool operator==(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  typename ft::Vector<T,Alloc>::const_iterator lit = lhs.begin(), rit = rhs.begin();
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

template<class T, class Alloc>
bool operator!=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
  return !(lhs == rhs);
}
template<class T, class Alloc>
bool operator<(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template<class T, class Alloc>
bool operator<=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
  return !(rhs < lhs);
}
template<class T, class Alloc>
bool operator>(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
  return rhs < lhs;
}
template<class T, class Alloc>
bool operator>=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
  return !(lhs < rhs);
}

template<class T, class Alloc>
void swap(List<T,Alloc>& lhs, List<T,Alloc>& rhs ) {
  lhs.swap(rhs);
}


}

#endif //FT_CONTAINERS_CONTAINERS_LIST_HPP_
