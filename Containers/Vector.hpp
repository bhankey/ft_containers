//
// Created by sergey on 11.04.2021.
//

#ifndef FT_CONTAINERS__VECTOR_HPP_
#define FT_CONTAINERS__VECTOR_HPP_

#include "VectorIterator.hpp"
#include "ReverseIterator.hpp"
#include <memory.h>

namespace ft {

template<typename T, typename Allocator = std::allocator<T> >
class Vector {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef VectorIterator<T> iterator;
  typedef VectorIterator<const T> const_iterator;
  typedef ReverseIterator<VectorIterator<T> > reverse_iterator;
  typedef ReverseIterator<VectorIterator<const T> > const_reverse_iterator;
 protected:
  pointer array_;
  allocator_type allocator_;
  size_t size_;
  size_t capacity_;
private:
  void moveToEnd(iterator start) {
    iterator pos = start;
    while (++pos != end()) {
      swap(start++, pos);
    }
  }
public:

  // Constructor and destructors
  explicit Vector(const Allocator& alloc = Allocator()): allocator_(alloc), size_(0), capacity_(0) {
    array_ = allocator_.allocate(0);
  }
  explicit Vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()): allocator_(alloc), size_(count), capacity_(count) {
    array_ = allocator_.allocate(size_);
    for (size_type i = 0; i < size_; ++i) {
      allocator_.construct(array_ + i, value);
    }
  }
//  template< class InputIt>
//      Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
  Vector(const Vector& other): allocator_(other.allocator_), size_(other.size_), capacity_(other.capacity_) {
    array_ = allocator_.allocate(capacity_);
    for (size_type i = 0; i < size_; ++i) {
      allocator_.construct(array_ + i, *(other.array_ + i));
    }
  }
  ~Vector() {
    for (size_type i = 0; i < size_; ++i) {
      allocator_.destroy(array_ + i);
    }
    allocator_.deallocate(array_, capacity_);
  }

  Vector &operator=(const Vector& other) {
    if (this != &other) {
     // clear();

    }
  }

  // Assign
  void assign(size_type count, const T& value);
  template<class InputIt>
  void assign(InputIt first, InputIt last);


  // Element access
  reference at(size_type pos);
  const_reference at(size_type pos) const {
    if (pos >= size_) {
      std::out_of_range("index out of range");
    }
    return *(array_ + pos);
  }
  reference operator[](size_type pos) {
    return *(array_ + pos);
  }
  const_reference operator[](size_type pos) const {
    return *(array_ + pos);
  }
  reference front() {
    return *array_;
  }
  const_reference front() const {
    return *array_;
  }
  reference back() {
    return *(array_ + size_ - 1);
  }
  const_reference back() const {
    return (array_ + size_ - 1);
  }

  // Iterators
  iterator begin() {
    return iterator(array_);
  }
  const_iterator begin() const {
    return const_iterator(array_);
  }
  iterator end() {
    return iterator(array_ + size_);
  }
  const_iterator end() const {
    return const_iterator(array_ + size_);
  }
  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() {
    return iterator(begin());
  }
  const_reverse_iterator rend() const {
    return const_iterator(begin());
  }

  // Capacity functions
  bool empty() const {
    return begin() == end();
  }
  size_type size() const {
    return size_;
  }
  size_type max_size() const {
    return allocator_.max_size();
  }
  void reserve(size_type new_cap);
  size_type capacity() const {
    return capacity_;
  }

  // Modifiers
  void clear();
  iterator insert(iterator pos, const T& value);
  void insert(iterator pos, size_type count,const T& value);
  template<class InputIt>
  void insert(iterator pos, InputIt first, InputIt last);
  iterator erase(iterator pos) {
    if (pos + 1 != end()) {

    }
    allocator_.destroy(array_ + size_ - 1);
    return pos;
  }
  iterator erase(iterator first, iterator last);
  void push_back(const T& value);
  void pop_back();
  void resize(size_type count, T value = T());
  void swap(Vector& other);
};

template<class T, class Alloc>
bool operator==(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs);
template<class T, class Alloc>
bool operator!=(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs);
template<class T, class Alloc>
bool operator<(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs);
template<class T, class Alloc>
bool operator>(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs);
template<class T, class Alloc>
bool operator<=(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs);
template<class T, class Alloc>
bool operator>=(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs);


}

#endif //FT_CONTAINERS__VECTOR_HPP_
