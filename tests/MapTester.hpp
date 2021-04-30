//
// Created by sergey on 29.04.2021.
//

#ifndef FT_CONTAINERS_TESTS_MAPTESTER_HPP_
#define FT_CONTAINERS_TESTS_MAPTESTER_HPP_

#include "print.hpp"

template<typename Pair>
void printPair(const Pair &pair) {
  std::cout << "[" << pair.first << ":" << pair.second << "] ";
}

template<typename Map>
void printMap(const Map &map) { // TODO test without reference
  typename Map::const_iterator it = map.begin();
  while (it != map.end()) {
    printPair(*it);
    ++it;
  }
  std::cout << std::endl;
}

template<typename Map>
void printMapReversed(const Map &map) { // TODO test without reference
  typename Map::const_iterator it = map.rbegin();
  while (it != map.rend()) {
    printPair(*it);
    ++it;
  }
  std::cout << std::endl;
}

template <typename Map>
void PrintMapInfo(const Map &map) { // TODO test without reference
  std::cout << "Map size: " << map.size() << " max_size: " << map.max_size() << std::endl;
  if (!map.empty()) {
    std::cout << "first: ";
    printPair(*map.begin());
    std::cout << " last: ";
    printPair(*(--map.end()));
    std::cout << std::endl;
  }
}

std::pair<int, std::string> GeneratePair() {
  static size_t i = 0;
  static int keys[50] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
  , 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46
  ,47, 48, 49, 50};
  if (i == 50) {
    i = 0;
  }
  std::pair<int, std::string> pair = std::make_pair(keys[i], "full");
  ++i;
  return pair;
}

template<typename Map>
void TestMap() {
  Map full;
  std::generate_n(std::inserter(full, full.begin()), 100, GeneratePair);
  PrintMapInfo(full);
  printMap(full);
}

#endif //FT_CONTAINERS_TESTS_MAPTESTER_HPP_
