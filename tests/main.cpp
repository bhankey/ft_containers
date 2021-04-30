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

#include "VectorTests.hpp"
#include "ListTests.hpp"
#include "MapTester.hpp"
#include "StackTest.hpp"
#include "QueueTests.hpp"

int main() {
  TestVector<ft::Vector<std::string> >();
  TestList<ft::List<std::string> >();
  TestMap<ft::Map<int, std::string> >();
  CustomCompareMyMap<ft::Map<int, std::string, std::greater<int> > >();
  TestStack<ft::Stack<std::string>, ft::List<std::string> >();
  TestQueue<ft::Queue<std::string>, ft::List<std::string> >();
//  std::map<int, std::string> a;
//  std::pair<int, std::string> b;
//  b.first = 5;
//  b.second = "lol";
//  a.insert(b);
//  b.second = "lal";
//  a.insert(b);
////  printByAlgorithms(a);
//for (std::map<int, std::string>::iterator it = a.begin(); it != a.end(); ++it) {
//  std::cout << "key: " << it->first << "; value: " << it->second << std::endl;
//}
  return 0;
}
