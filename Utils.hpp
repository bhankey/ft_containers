//
// Created by sergey on 15.04.2021.
//

#ifndef FT_CONTAINERS__UTILS_HPP_
#define FT_CONTAINERS__UTILS_HPP_

#include <iostream>

namespace ft {

template<typename Iter>
size_t distance(Iter first, Iter last) {
  size_t distance = 0;
  while (first != last) {
    ++distance;
    ++first;
  }
  return distance;
}

template<typename Iter>
void advance(Iter &it, size_t count) {
  while (count) {
    ++it;
    --count;
  }
}

}

#endif //FT_CONTAINERS__UTILS_HPP_
