//
// Created by sergey on 11.04.2021.
//

#ifndef FT_CONTAINERS__VECTOR_HPP_
#define FT_CONTAINERS__VECTOR_HPP_

#include "VectorIterator.hpp"
#include "Reverseiterator.hpp"

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
 private:
  value_type
};

}

#endif //FT_CONTAINERS__VECTOR_HPP_
