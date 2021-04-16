#include <iostream>
#include "Containers/Vector.hpp"
#include <vector>

int main() {
  ft::Vector<int>  a(2, 10);
  for (ft::Vector<int>::reverse_iterator it = a.rbegin(); it != a.rend(); ++it) {
    std::cout << *it << std::endl;
  }
  return 0;
}
