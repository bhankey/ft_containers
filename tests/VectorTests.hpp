//
// Created by sergey on 18.04.2021.
//

#ifndef FT_CONTAINERS_TESTS_VECTORTESTS_HPP_
#define FT_CONTAINERS_TESTS_VECTORTESTS_HPP_

#include "print.hpp"
#include <algorithm>

template<typename Vector>
void PrintVectorInfo(Vector vec) {
  std::cout << "Vec size: " << vec.size() << " capacity: " << vec.capacity() << " max_size: " << vec.max_size() << std::endl;
  if (!vec.empty()) {
    std::cout << "back: " << vec.back() << " front: " << vec.front() << std::endl;
  }
}

template<typename Container>
void printNormal(const Container container) {
  for (size_t i = 0; i < container.size(); ++i) {
    std::cout << container[i] << " ";
  }
  std::cout << std::endl;
}

template<typename Vector>
void TestVector() {
  std::cout << "Vector testing" << std::endl;
  std::cout << "Testing constructors, operation '=' and assign" << std::endl;
  Vector full(100, "full");
  {
    Vector vec;
    printNormal(vec);
    PrintVectorInfo(vec);
  }
  {
    Vector vec(10, "5");
    printIterator(vec);
    PrintVectorInfo(vec);
    const Vector vec1(vec);
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
  }
  {
    Vector vec(11);
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
  }
  {
    ft::List<typename Vector::value_type> l;
    l.push_back("pam");
    l.push_back("ram");
    l.push_back("lll");
    Vector vec(l.begin(), l.end());
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    Vector vec1;
    vec1.push_back("tmp");
    vec1 = vec;
    printByAlgorithms(vec1);
    PrintVectorInfo(vec1);
  }
  {
    Vector toCopy(10);
    toCopy[0] = "pam";
    toCopy[2] = "ram";
    toCopy[6] = "lll";
    Vector vec(toCopy);
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    Vector vec1;
    vec1.assign(5, "l");
    printByAlgorithms(vec);
    PrintVectorInfo(vec1);
    vec1.assign(toCopy.begin(), toCopy.end());
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
  }
  {
    Vector vec;
    Vector vec1;
    vec = vec1;
    PrintVectorInfo(vec);
    PrintVectorInfo(vec1);
  }
  std::cout << "Testing some special cases of element access" << std::endl;
  {
    Vector vec;
    try {
      std::cout << vec.at(11) << std::endl;
    }
    catch (...) {
      std::cout << "exception caught" << std::endl;
    }
    vec.push_back("aaa");
    try {
      std::cout << vec.at(0) << std::endl;
    }
    catch (...) {
      std::cout << "exception caught" << std::endl;
    }
    printNormal(vec);
    PrintVectorInfo(vec);
    printNormal(full);
  }
  std::cout << "Test reserve" << std::endl;
  {
    Vector vec(100);
    vec.reserve(1);
    PrintVectorInfo(vec);
    vec.reserve(1000);
    PrintVectorInfo(vec);
  }
  std::cout << "Test some modifiers" << std::endl;
  {
    Vector vec;
    vec.clear();
    vec.insert(vec.begin(), "first");
    PrintVectorInfo(vec);
    printByAlgorithms(vec);
    vec.clear();
    vec.insert(vec.end(), "end");
    PrintVectorInfo(vec);
    printByAlgorithms(vec);
    vec.pop_back();
    PrintVectorInfo(vec);
    vec.push_back("1");
    PrintVectorInfo(vec);
    vec.swap(full);
    PrintVectorInfo(vec);
    printByAlgorithms(vec);
    PrintVectorInfo(full);
    printByAlgorithms(full);
    full.swap(vec);
    PrintVectorInfo(vec);
    printByAlgorithms(vec);
    PrintVectorInfo(full);
    printByAlgorithms(full);
    vec.resize(0);
    PrintVectorInfo(vec);
    vec.resize(100);
    TestCompare(vec, full);
    PrintVectorInfo(vec);
    printByAlgorithms(vec);
  }
  std::cout << "Complex test" << std::endl;
  {
    Vector vec;
    vec.insert(vec.begin(), 30, "lol");
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.insert(vec.begin() + 4, "pam");
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    ft::List<typename Vector::value_type> l;
    l.push_back("pam");
    l.push_back("ram");
    l.push_back("lll");
    vec.insert(vec.begin() + 2, l.begin(), l.end());
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.erase(vec.begin() + 4);
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.erase(vec.begin(), vec.begin() + 5);
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.erase(vec.begin(), vec.end());
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.push_back("ppp");
    vec.push_back("rrrr");
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.pop_back();
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.resize(100);
    vec.at(99) = "30";
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.clear();
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.assign(20, "pam");
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.resize(10);
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec[5] = "1";
    std::sort(vec.begin(), vec.end());
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    Vector vec1(vec);
    TestCompare(vec, vec1);
    vec[1] = "5";
    TestCompare(vec, vec1);
    vec.resize(0);
    TestCompare(vec, vec1);
    vec1.resize(0);
    TestCompare(vec, vec1);
  }
  std::cout << "Test cases of Vector ended. Compare results with std" << std::endl;
}

#endif //FT_CONTAINERS_TESTS_VECTORTESTS_HPP_
