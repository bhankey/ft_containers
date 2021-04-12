//
// Created by sergey on 11.04.2021.
//

#ifndef FT_CONTAINERS_ITERATORS_VECTORITERATOR_HPP_
#define FT_CONTAINERS_ITERATORS_VECTORITERATOR_HPP_

namespace ft {

template<typename Type>
class VectorIterator {
 public:
  typedef std::random_access_iterator_tag iterator_category;
  typedef Type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef Type *pointer;
  typedef Type &reference;
 private:
  pointer p;
 public:
  VectorIterator() : p(NULL) {
  };
  VectorIterator(const pointer _p): p(_p) {
  }
  VectorIterator(const VectorIterator<Type> &it) : p(it.p) {
  };
  VectorIterator &operator=(const VectorIterator<Type> &it) {
    p = it.p;
    return *this;
  }
  ~VectorIterator() {
  };



  reference operator*() const {
    return *p;
  }
  pointer operator->() const {
    return p;
  }

  // Increment
  VectorIterator &operator++() {
    ++p;
    return *this;
  }
  VectorIterator operator++(int) {
    VectorIterator<Type> tmp(*this);
    ++p;
    return tmp;
  }

  // Decrement
  VectorIterator &operator--() {
    --p;
    return *this;
  }
  VectorIterator operator--(int) {
    VectorIterator<Type> tmp(*this);
    --p;
    return tmp;
  }

  // Arithmetic operators
  VectorIterator operator+(difference_type diff) const {
    return VectorIterator<Type>(p + diff);
  }
  VectorIterator operator-(difference_type diff) const {
    return VectorIterator<Type>(p - diff);
  }
  VectorIterator &operator+=(difference_type diff) {
    p += diff;
    return *this;
  }
  VectorIterator &operator-=(difference_type diff) {
    p -= diff;
    return *this;
  }

  reference operator[](difference_type offset) const {
    return p[offset];
  }

// Compare functions
  inline bool operator==(const VectorIterator<Type> &it) const {
    return p == it.p;
  }
  inline bool operator!=(const VectorIterator<Type> &it) const {
    return p != it.p;
  }
  inline bool operator<(const VectorIterator<Type> &it) const {
    return p < it.p;
  }
  inline bool operator>(const VectorIterator<Type> &it) const {
    return p > it.p;
  }
  inline bool operator<=(const VectorIterator<Type> &it) const {
    return p <= it.p;
  }
  inline bool operator>=(const VectorIterator<Type> &it) const {
    return p >= it.p;
  }

};

class ReverseVectorIterator {
 public:

};

}
#endif //FT_CONTAINERS_ITERATORS_VECTORITERATOR_HPP_
