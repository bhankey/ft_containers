//
// Created by sergey on 17.04.2021.
//

#ifndef FT_CONTAINERS_FUNCTIONSFORTEST_PRINT_HPP_
#define FT_CONTAINERS_FUNCTIONSFORTEST_PRINT_HPP_

#include <iterator>
#include "Vector.hpp"

template<typename Container>
void printNormal(const Container container) {
  for (size_t i = 0; i < container.size(); ++i) {
    std::cout << container[i] << " ";
  }
  std::cout << std::endl;
}

template<typename Container>
void printIterator(const Container container) {
  typename Container::const_iterator it = container.begin();
  while (it != container.end()) {
    std::cout << *it << " ";
    it++;
  }
  std::cout << std::endl;
}

template<typename Container>
void printByAlgorithms(const Container &c) {
  std::copy(c.begin(), c.end(), std::ostream_iterator<typename Container::value_type>(std::cout, " "));
  std::cout << std::endl;
}

#endif //FT_CONTAINERS_FUNCTIONSFORTEST_PRINT_HPP_
