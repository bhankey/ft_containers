#include <iostream>

#include "print.hpp"
#include <map>
#include <deque>
#include <vector>

#include "List.hpp"
#include "Vector.hpp"

#include "VectorTests.hpp"
#include "ListTests.hpp"

int main() {
 // TestVector<ft::Vector<std::string> >();
 TestVector<std::vector<std::string> >();
 // TestList<ft::List<std::string> >();
 // TestList<std::list<std::string> >();
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
