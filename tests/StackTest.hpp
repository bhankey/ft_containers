//
// Created by sergey on 30.04.2021.
//

#ifndef FT_CONTAINERS_TESTS_STACKTEST_HPP_
#define FT_CONTAINERS_TESTS_STACKTEST_HPP_

#include "print.hpp"

template<typename Stack>
void PrintStackInfo(const Stack &stack) {
  std::cout << "Map size: " << stack.size() << std::endl;
  if (!stack.empty()) {
    std::cout << stack.top() << std::endl;
  }
}
template<typename Stack>
void PrintStack(Stack &stack) {
  while (!stack.empty()) {
    std::cout << stack.top() << " ";
    stack.pop();
  }
  std::cout << std::endl;
}

template<typename Stack, typename Container>
void TestStack() {
  std::cout << "Testing Stack" << std::endl;
  Container a(10, "22222");
  Stack full(a);
  Stack s(full);
  PrintStackInfo(full);
  PrintStack(full);

  PrintStackInfo(s);
  PrintStack(s);
  full.push("222");
  s = full;
  PrintStackInfo(s);
  PrintStack(s);
  s.push("2222");
  s.pop();
  PrintStackInfo(s);
  PrintStack(s);
  Stack full1(a);
  for (size_t i = 0; i < 1000; ++i) {
    full1.push("ff");
  }
  PrintStackInfo(full1);
  PrintStack(full1);
  const Stack kStack(a);
  std::cout << kStack.top() << " " << kStack.size() << " " << kStack.empty();
};
#endif //FT_CONTAINERS_TESTS_STACKTEST_HPP_
