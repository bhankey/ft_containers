#include <iostream>
#include "Vector.hpp"
#include <vector>
#include "print.hpp"

#include "VectorTests.hpp"


int main() {
  TestVector<ft::Vector<std::string> >();
  TestVector<std::vector<std::string> >();
  return 0;
}
