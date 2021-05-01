//
// Created by sergey on 13.04.2021.
//

#ifndef FT_CONTAINERS_ITERATORS_REVERSEITERATOR_HPP_
#define FT_CONTAINERS_ITERATORS_REVERSEITERATOR_HPP_

namespace ft {

template<typename Iter>
class ReverseIterator {
 public:
  typedef typename Iter::iterator_category iterator_category;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
 private:
  Iter it;
 public:
  ReverseIterator() : it() {
  }
  ReverseIterator(const ReverseIterator<Iter> &_it) : it(_it.base()) {
  }
  ReverseIterator(const Iter &_it) : it(_it) {
  }
  ReverseIterator &operator=(const ReverseIterator &_it) {
    it = _it.it;
    return *this;
  }
  ~ReverseIterator() {
  }

  Iter base() const {
    return it;
  }
  reference operator*() const {
    Iter tmp(it);
    return (*--tmp);
  }
  pointer operator->() const {
    return &(operator*());
  }

  // Increment and Decrement
  ReverseIterator &operator++() {
    --it;
    return *this;
  }
  ReverseIterator operator++(int) {
    ReverseIterator tmp(*this);
    --it;
    return tmp;
  }
  ReverseIterator &operator--() {
    ++it;
    return *this;
  }
  ReverseIterator operator--(int) {
    ReverseIterator tmp(*this);
    ++it;
    return tmp;
  }

  // Arithmetic operators (Only for random access iterator)
  ReverseIterator operator+(difference_type diff) const {
    return ReverseIterator(it - diff);
  }
  ReverseIterator &operator+=(difference_type diff) {
    it -= diff;
    return *this;
  }
  ReverseIterator operator-(difference_type diff) const {
    return ReverseIterator(it + diff);
  }
  difference_type operator-(const ReverseIterator &iter) const {
    return (iter.it - it);
  }
  ReverseIterator &operator-=(difference_type diff) {
    it += diff;
    return *this;
  }

  // Only for random access iterator
  reference operator[](difference_type offset) const {
    return it[offset];
  }
};

template<typename Iter>
inline bool operator==(const ReverseIterator<Iter> &left, const ReverseIterator<Iter> &right) {
  return left.base() == right.base();
}
template<typename Iter>
inline bool operator!=(const ReverseIterator<Iter> &left, const ReverseIterator<Iter> &right) {
  return left.base() != right.base();
}
template<typename Iter>
inline bool operator<(const ReverseIterator<Iter> &left, const ReverseIterator<Iter> &right) {
  return left.base() < right.base();
}
template<typename Iter>
inline bool operator>(const ReverseIterator<Iter> &left, const ReverseIterator<Iter> &right) {
  return left.base() > right.base();
}
template<typename Iter>
inline bool operator<=(const ReverseIterator<Iter> &left, const ReverseIterator<Iter> &right) {
  return left.base() <= right.base();
}
template<typename Iter>
inline bool operator>=(const ReverseIterator<Iter> &left, const ReverseIterator<Iter> &right) {
  return left.base() >= right.base();
}

}

#endif //FT_CONTAINERS_ITERATORS_REVERSEITERATOR_HPP_
