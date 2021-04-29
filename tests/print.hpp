//
// Created by sergey on 17.04.2021.
//

#ifndef FT_CONTAINERS_FUNCTIONSFORTEST_PRINT_HPP_
#define FT_CONTAINERS_FUNCTIONSFORTEST_PRINT_HPP_

#include <iterator>
#include "Vector.hpp"

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
template<typename Container>
void printByAlgorithmsReverse(const Container &c) {
  std::copy(c.rbegin(), c.rend(), std::ostream_iterator<typename Container::value_type>(std::cout, " "));
  std::cout << std::endl;
}

template<typename Container>
void TestCompare(Container &f, Container &s) {
  std::cout << (f == s) << " " << (f != s) << " " << (f < s) << " " << (f <= s) << " " << (f > s) << " " << (f >= s) << std::endl;
}


#endif //FT_CONTAINERS_FUNCTIONSFORTEST_PRINT_HPP_
