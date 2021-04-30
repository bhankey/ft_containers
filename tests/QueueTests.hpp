//
// Created by sergey on 30.04.2021.
//

#ifndef FT_CONTAINERS_TESTS_QUEUETESTS_HPP_
#define FT_CONTAINERS_TESTS_QUEUETESTS_HPP_

#include "print.hpp"

template<typename Queue>
void PrintQueueInfo(const Queue &queue) {
  std::cout << "Map size: " << queue.size() << std::endl;
  if (!queue.empty()) {
    std::cout << "front: " << queue.front() << "back: " << queue.back();
  }
}
template<typename Queue>
void PrintQueue(Queue &queue) {
  while (!queue.empty()) {
    std::cout << queue.front() << " ";
    queue.pop();
  }
  std::cout << std::endl;
}

template<typename Queue, typename Container>
void TestQueue() {
  std::cout << "Testing Queue" << std::endl;
  Container a(10, "22222");
  Queue full(a);
  Queue s(full);
  PrintQueueInfo(full);
  PrintQueue(full);

  PrintQueueInfo(s);
  PrintQueue(s);
  full.push("222");
  s = full;
  PrintQueueInfo(s);
  PrintQueue(s);
  s.push("2222");
  s.pop();
  PrintQueueInfo(s);
  PrintQueue(s);
  Queue full1(a);
  for (size_t i = 0; i < 1000; ++i) {
    full1.push("ff");
  }
  PrintQueueInfo(full1);
  PrintQueue(full1);
  const Queue kQueue(a);
  std::cout << kQueue.back() << " " << kQueue.front() << " " << kQueue.size() << " " << kQueue.empty();
};

#endif //FT_CONTAINERS_TESTS_QUEUETESTS_HPP_
