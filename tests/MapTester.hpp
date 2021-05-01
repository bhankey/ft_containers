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
void printInsertRes(const std::pair<typename Map::iterator, bool> &pair) {
  std::cout << std::boolalpha << pair.second << " - ";
  if (pair.second == true) {
    printPair(*(pair.first));
  }
  else {
    std::cout << "none";
  }
  std::cout << std::endl;
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
  typename Map::const_reverse_iterator it = map.rbegin();
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
  std::cout << "Map Test" << std::endl;
  std::cout << "Testing constructor, operator =" << std::endl;
  Map full;
  std::generate_n(std::inserter(full, full.begin()), 100, GeneratePair);
  PrintMapInfo(full);
  printMap(full);
  {
    std::list<std::pair<int, std::string> > l;
    l.push_back(std::make_pair(1, "1"));
    l.push_back(std::make_pair(2, "2"));
    l.push_back(std::make_pair(3, "3"));
    l.push_back(std::make_pair(1, "!1"));
    l.push_back(std::make_pair(4, "4"));
    Map iter(l.begin(), l.end());
    PrintMapInfo(iter);
    printMap(iter);
    Map copy(full);
    TestCompare(copy, iter);
    PrintMapInfo(copy);
    printMap(copy);
    copy = iter;
    TestCompare(copy, iter);
    iter.clear();
    PrintMapInfo(copy);
    printMap(copy);
    copy.clear();
    copy = full;
    PrintMapInfo(copy);
    printMap(copy);
  }
  std::cout << "Test element access" << std::endl;
  {
    Map map(full);
    map[1] = "hmmm";
    map[30] = "dd";
    map[50] = "pam";
    PrintMapInfo(map);
    printMap(map);
    printMapReversed(map);
    map[51] = "51";
    map[100] = "100";
    map[33333] = "33333333";
    PrintMapInfo(map);
    printMap(map);
  }
  std::cout << "Test modifiers" << std::endl;
  {
    Map map(full);
    map.clear();
    PrintMapInfo(map);
    printMap(map);
    map.insert(full.begin(), full.end());
    PrintMapInfo(map);
    printMap(map);
    std::cout << "res of insertion";
    printInsertRes<Map>(map.insert(std::make_pair(1000, "1234")));
    PrintMapInfo(map);
    printMap(map);
    map.clear();
    std::cout << "res of insertion";
    printInsertRes<Map>(map.insert(std::make_pair(1, "1234")));
    std::cout << "res of insertion";
    printInsertRes<Map>(map.insert(std::make_pair(1, "123")));
    std::cout << "res of insertion";
    printInsertRes<Map>(map.insert(std::make_pair(2, "2234")));
    PrintMapInfo(map);
    printMap(map);
    std::cout << "erase: " << map.erase(5) << " " << std::endl;
    PrintMapInfo(map);
    printMap(map);
    printMapReversed(map);
    std::cout << "erase: " << map.erase(2) << " " << std::endl;
    PrintMapInfo(map);
    printMap(map);
    std::cout << "erase: " << map.erase(1) << " " << std::endl;
    PrintMapInfo(map);
    printMap(map);
    map.insert(full.begin(), full.end());
    map.insert(full.begin(), full.end());
    std::cout << "erase: " << map.erase(2) << " " << std::endl;
    PrintMapInfo(map);
    printMap(map);
    map.erase(map.begin());
    map.erase(--map.end());
    map.erase(++map.begin());
    PrintMapInfo(map);
    printMap(map);
    map.erase(++map.begin(), --map.end());
    PrintMapInfo(map);
    printMap(map);
    map.erase(map.begin(), map.end());
    PrintMapInfo(map);
    printMap(map);
    map.insert(full.begin(), full.end());
    Map map1;
    map1.swap(map);
    PrintMapInfo(map);
    printMap(map);
    PrintMapInfo(map1);
    printMap(map1);
    map.swap(map1);
    TestCompare(map1, map);
  }
  std::cout << "Test lookup methods" << std::endl;
  {
    Map map(full);
    TestCompare(full, map);
    std::cout << map.count(1);
    map.insert(full.begin(), full.end());
    std::cout << map.count(1);
    typename Map::iterator it = map.find(5);
    if (it != map.end()) {
      printPair(*it);
    }
    it = map.find(29);
    if (it != map.end()) {
      printPair(*it);
    }
    it = map.find(-5);
    if (it != map.end()) {
      printPair(*it);
    }
    typename Map::iterator lower, upper;
    lower = map.lower_bound(10);
    upper = map.upper_bound(10);
    map.erase(lower, upper);
    PrintMapInfo(map);
    printMap(map);
    TestCompare(full, map);
    lower = map.lower_bound(1000);
    upper = map.upper_bound(1000);
    map.erase(lower, upper);
    PrintMapInfo(map);
    printMap(map);
    lower = map.lower_bound(1);
    upper = map.upper_bound(1000);
    map.erase(lower, upper);
    PrintMapInfo(map);
    printMap(map);
  }
}

template<typename Map>
void CustomCompareMyMap() {
  std::cout << "Testing with not default compare" << std::endl;
  std::greater<int> a;
  Map map(a);
  std::generate_n(std::inserter(map, map.begin()), 100, GeneratePair);
  PrintMapInfo(map);
  printMap(map);
}

#endif //FT_CONTAINERS_TESTS_MAPTESTER_HPP_
