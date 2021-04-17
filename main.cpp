#include <iostream>
#include "Containers/Vector.hpp"
#include <vector>
#include "print.hpp"

int main() {

  ft::Vector<std::string> strings(2, "lol");
  strings.insert(strings.begin() + 1 , 100, "pam");
  printNormal(strings);
  printIterator(strings);
  printByAlgorithms(strings);
  return 0;
}
