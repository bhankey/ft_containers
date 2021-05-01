//
// Created by shultsevamarina on 01.05.2021.
//

#ifndef FT_CONTAINERS_TESTS_MULTISETTESTS_HPP_
#define FT_CONTAINERS_TESTS_MULTISETTESTS_HPP_

#include "SetTests.hpp"

template<typename Set>
void TestMultiset() {
  std::cout << "Multiset Test" << std::endl;
  std::cout << "Testing constructor, operator =" << std::endl;
  Set full;
  std::generate_n(std::inserter(full, full.begin()), 100, GenerateString);
  PrintSetInfo(full);
  printByAlgorithms(full);
  {
    std::list<std::string> l;
    l.push_back("1");
    l.push_back("2");
    l.push_back("3");
    l.push_back("!1");
    l.push_back("4");
    Set iter(l.begin(), l.end());
    PrintSetInfo(iter);
    printByAlgorithms(iter);
    Set copy(full);
    TestCompare(copy, iter);
    PrintSetInfo(copy);
    printByAlgorithms(copy);
    copy = iter;
    TestCompare(copy, iter);
    iter.clear();
    PrintSetInfo(copy);
    printByAlgorithms(copy);
    copy.clear();
    copy = full;
    PrintSetInfo(copy);
    printByAlgorithms(copy);
  }
  std::cout << "Test modifiers" << std::endl;
  {
    Set set(full);
    set.clear();
    PrintSetInfo(set);
    printByAlgorithms(set);
    set.insert(full.begin(), full.end());
    PrintSetInfo(set);
    printByAlgorithms(set);
    std::cout << "res of insert: " << *set.insert("1234") << std::endl;
    PrintSetInfo(set);
    printByAlgorithms(set);
    set.clear();
    std::cout << "res of insert: " << *set.insert("1234") << std::endl;
    std::cout << "res of insert: " << *set.insert("2234") << std::endl;
    std::cout << "res of insert: " << *set.insert("1234") << std::endl;
    PrintSetInfo(set);
    printByAlgorithms(set);
    std::cout << "erase: " << set.erase("1") << " " << std::endl;
    PrintSetInfo(set);
    printByAlgorithms(set);
    printByAlgorithmsReverse(set);
    std::cout << "erase: " << set.erase("2") << " " << std::endl;
    PrintSetInfo(set);
    printByAlgorithms(set);
    std::cout << "erase: " << set.erase("-1") << " " << std::endl;
    PrintSetInfo(set);
    printByAlgorithms(set);
    set.insert(full.begin(), full.end());
    set.insert(full.begin(), full.end());
    std::cout << "erase: " << set.erase("2") << " " << std::endl;;
    PrintSetInfo(set);
    printByAlgorithms(set);
    set.erase(set.begin());
    set.erase(--set.end());
    set.erase(++set.begin());
    PrintSetInfo(set);
    printByAlgorithms(set);
    set.erase(++set.begin(), --set.end());
    PrintSetInfo(set);
    printByAlgorithms(set);
    set.erase(set.begin(), set.end());
    PrintSetInfo(set);
    printByAlgorithms(set);
    set.insert(full.begin(), full.end());
    Set set1;
    set1.swap(set);
    PrintSetInfo(set);
    printByAlgorithms(set);
    PrintSetInfo(set1);
    printByAlgorithms(set1);
    set.swap(set1);
    TestCompare(set1, set);
  }
  std::cout << "Test lookup methods" << std::endl;
  {
    Set set(full);
    TestCompare(full, set);
    std::cout << set.count("1");
    set.insert(full.begin(), full.end());
    std::cout << set.count("1");
    typename Set::iterator it = set.find("5");
    if (it != set.end()) {
      std::cout << *it;
    }
    it = set.find("29");
    if (it != set.end()) {
      std::cout << *it;
    }
    it = set.find("-5");
    if (it != set.end()) {
      std::cout << *it;
    }
    typename Set::iterator lower, upper;
    lower = set.lower_bound("10");
    upper = set.upper_bound("10");
    set.erase(lower, upper);
    PrintSetInfo(set);
    printByAlgorithms(set);
    printByAlgorithmsReverse(set);
    TestCompare(full, set);
    lower = set.lower_bound("1000");
    upper = set.upper_bound("1000");
    set.erase(lower, upper);
    PrintSetInfo(set);
    printByAlgorithms(set);
    lower = set.lower_bound("1");
    upper = set.upper_bound("1000");
    set.erase(lower, upper);
    PrintSetInfo(set);
    printByAlgorithms(set);
  }
}

#endif //FT_CONTAINERS_TESTS_MULTISETTESTS_HPP_
