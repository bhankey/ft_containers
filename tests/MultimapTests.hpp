//
// Created by sergey on 01.05.2021.
//

#ifndef FT_CONTAINERS_TESTS_MULTIMAPTESTS_HPP_
#define FT_CONTAINERS_TESTS_MULTIMAPTESTS_HPP_

#include "MapTester.hpp"

template<typename Map>
void TestMultimap() {
  std::cout << "Multimap Test" << std::endl;
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
    map.insert(std::make_pair(1000, "1234"));
    PrintMapInfo(map);
    printMap(map);
    map.clear();
    std::cout << "res of insertion";
    map.insert(std::make_pair(1, "1234"));
    std::cout << "res of insertion";
    map.insert(std::make_pair(1, "123"));
    std::cout << "res of insertion";
    map.insert(std::make_pair(2, "2234"));
    PrintMapInfo(map);
    printMap(map);
    std::cout << "erase: " << map.erase(5) << std::endl;
    PrintMapInfo(map);
    printMap(map);
    printMapReversed(map);
    std::cout << "erase: " << map.erase(2) << std::endl;
    PrintMapInfo(map);
    printMap(map);
    std::cout << "erase: " << map.erase(1) << std::endl;
    PrintMapInfo(map);
    printMap(map);
    map.insert(full.begin(), full.end());
    map.insert(full.begin(), full.end());
    std::cout << "erase: " << map.erase(2);
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


#endif //FT_CONTAINERS_TESTS_MULTIMAPTESTS_HPP_
