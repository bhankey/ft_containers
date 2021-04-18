//
// Created by sergey on 11.04.2021.
//

#ifndef FT_CONTAINERS__VECTOR_HPP_
#define FT_CONTAINERS__VECTOR_HPP_

#include "VectorIterator.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"
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
      std::swap(*start, *pos);
      start++;
    }
  }
  void moveToRight(size_type start, difference_type offset) {
    size_type index_end = end().operator->() - begin().operator->();
    size_type tmp = index_end - 1;
    size_type count = index_end - start;
    size_ += offset;
    --offset;
    while (count > 0) {
      allocator_.construct(array_ + index_end + offset, *(array_ + tmp));
      allocator_.destroy(array_ + tmp);
      --index_end;
      --tmp;
      --count;
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
  template< class InputIt>
  Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()): allocator_(alloc) {
    size_ = ft::distance(first, last);
    capacity_ = size_;
    array_ = allocator_.allocate(size_);
    for (size_type i = 0; first != last; ++first, ++i) {
      allocator_.construct(array_ + i, *first);
    }
  }
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
  void assign(size_type count, const T& value) {
    clear();
    insert(begin(), count, value);
  }
  template<class InputIt>
  void assign(InputIt first, InputIt last) {
    clear();
    insert(begin(), first, last);
  }

  // Element access
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("index out of range");
    }
    return *(array_ + pos);
  }
  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("index out of range");
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
  size_type capacity() const {
    return capacity_;
  }
  void reserve(size_type new_cap) {
    if (new_cap > capacity_) {
      pointer new_array = allocator_.allocate(new_cap);
      for (size_type i = 0; i < size_; ++i) {
        allocator_.construct(new_array + i, *(array_ +i));
        allocator_.destroy(array_ + i);
      }
      allocator_.deallocate(array_, capacity_);
      capacity_ = new_cap;
      array_ = new_array;
    }
  }

  // Modifiers
  void clear() {
    erase(begin(), end());
  }
  iterator insert(iterator pos, const T& value) {
    size_type index_pos = pos.operator->() - begin().operator->();
    if (size_ == capacity_) {
      if (size_ == 0) {
        reserve(1);
      } else {
        reserve((capacity_ ) + 1);
      }
    }
    if (pos == end()) {
      push_back(value);
      return (end() - 1);
    }
    moveToRight(index_pos, 1);
    allocator_.construct((array_ + index_pos), value);
    return iterator(array_ + index_pos);
  }
  void insert(iterator pos, size_type count, const T& value){
    size_type index_pos = pos.operator->() - begin().operator->();
    if (size_ + count > capacity_) {
      reserve(static_cast<size_type>((capacity_)) + count);
    }
    if (pos == end()) {
      while (count > 0) {
        push_back(value);
        --count;
      }
      return;
    }
    moveToRight(index_pos, count);
    size_type tmp = index_pos;
    while (count > 0) {
      allocator_.construct(array_ + tmp, value);
      ++tmp;
      --count;
    }
  }
  template<class InputIt>
  void insert(iterator pos, InputIt first, InputIt last) {
    while (first != last) {
      pos = insert(pos, *first) + 1;
      ++first;
    }
  }
  iterator erase(iterator pos) {
    if (pos + 1 != end()) {
      moveToEnd(pos);
    }
    allocator_.destroy(array_ + size_ - 1);
    --size_;
    return pos;
  }
  iterator erase(iterator first, iterator last) {
      while (first != last) {
        erase(first);
        --last;
      }
    return first;
  }
  void pop_back() {
    if (size_ != 0) {
      erase(end() - 1);
    }
  }
  void push_back(const T& value) {
    if (size_ == capacity_) {
      if (size_ == 0) {
        reserve(1);
      } else {
        reserve((capacity_ * 1.5f) + 1);
      }
    }
    allocator_.construct(array_ + size_, value);
    size_++;
  }
  void resize(size_type count, T value = T()) {
    if (count > capacity_) {
      reserve(count);
    }
    if (count > size_) {
      while(count != size_) {
        allocator_.construct(array_ + size_, value);
        size_++;
      }
    } else if (count < size_) {
      erase(iterator(array_ + count), end());
    }
  }
  void swap(Vector& other) {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(allocator_, other.allocator_);
  }
};

template<class T, class Alloc>
bool operator==(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs) {
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
bool operator!=(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs) {
  return !(lhs == rhs);
}
template<class T, class Alloc>
bool operator<(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template<class T, class Alloc>
bool operator>(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs) {
  return rhs < lhs;
}
template<class T, class Alloc>
bool operator<=(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs) {
  return !(rhs < lhs);
}
template<class T, class Alloc>
bool operator>=(const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs) {
  return !(lhs < rhs);
}
template< class T, class Alloc >
void swap(ft::Vector<T,Alloc>& lhs, ft::Vector<T,Alloc>& rhs) {
  lhs.swap(rhs);
}


}

#endif //FT_CONTAINERS__VECTOR_HPP_
