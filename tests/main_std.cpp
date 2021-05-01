//
// Created by sergey on 18.04.2021.
//

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <list>
#include <stack>
#include <set>

#include "VectorTests.hpp"
#include "ListTests.hpp"
#include "MapTester.hpp"
#include "StackTest.hpp"
#include "QueueTests.hpp"
#include "MultimapTests.hpp"
#include "SetTests.hpp"
#include "MultisetTests.hpp"

int main() {
  TestVector<std::vector<std::string> >();
  TestList<std::list<std::string> >();
  TestMap<std::map<int, std::string> >();
  CustomCompareMyMap<std::map<int, std::string, std::greater<int> > >();
  TestStack<std::stack<std::string, std::list<std::string> >, std::list<std::string> >();
  TestQueue<std::queue<std::string, std::list<std::string> >, std::list<std::string> >();
  std::cout << "Bonus part" << std::endl;
  TestMultimap<std::multimap<int, std::string> >();
  TestSet<std::set<std::string> >();
  TestMultiset<std::multiset<std::string> >();
  return 0;
}