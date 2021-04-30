#include <iostream>

#include "print.hpp"
#include <map>
#include <deque>
#include <vector>

#include "List.hpp"
#include "Vector.hpp"
#include "Map.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Multimap.hpp"

#include "VectorTests.hpp"
#include "ListTests.hpp"
#include "MapTester.hpp"
#include "StackTest.hpp"
#include "QueueTests.hpp"
#include "MultimapTests.hpp"

int main() {
  TestVector<ft::Vector<std::string> >();
  TestList<ft::List<std::string> >();
  TestMap<ft::Map<int, std::string> >();
  CustomCompareMyMap<ft::Map<int, std::string, std::greater<int> > >();
  TestStack<ft::Stack<std::string>, ft::List<std::string> >();
  TestQueue<ft::Queue<std::string>, ft::List<std::string> >();
  std::cout << "Bonus part" << std::endl;
  TestMultimap<ft::Multimap<int, std::string> >();
  return 0;
}
