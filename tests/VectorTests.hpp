//
// Created by sergey on 18.04.2021.
//

#ifndef FT_CONTAINERS_TESTS_VECTORTESTS_HPP_
#define FT_CONTAINERS_TESTS_VECTORTESTS_HPP_

#include "print.hpp"
#include <list>
#include <algorithm>

template<typename Vector>
void PrintVectorInfo(Vector vec) {
  std::cout << "Vec size: " << vec.size() << " capacity: " << vec.capacity() << " max_size: " << vec.max_size() << std::endl;
  if (!vec.empty()) {
    std::cout << "back: " << vec.back() << " front: " << vec.front() << std::endl;
  }
}
template<typename Vector>
void TestVector() {
  {
    Vector vec;
    printNormal(vec);
    PrintVectorInfo(vec);
  }
  {
    Vector vec(10, "5");
    printIterator(vec);
    PrintVectorInfo(vec);
  }
  {
    Vector vec(11);
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
  }
  {
    std::list<typename Vector::value_type> l;
    l.push_back("pam");
    l.push_back("ram");
    l.push_back("lll");
    Vector vec(l.begin(), l.end());
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
  }
  {
    Vector toCopy(10);
    toCopy[0] = "pam";
    toCopy[2] = "ram";
    toCopy[6] = "lll";
    Vector vec(toCopy);
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
  }
  {
    Vector vec;
    vec.insert(vec.begin(), 30, "lol");
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    vec.insert(vec.begin() + 4, "pam");
    printByAlgorithms(vec);
    PrintVectorInfo(vec);
    std::list<typename Vector::value_type> l;
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
    std::cout << (vec == vec1) << std::endl;
    std::cout << (vec < vec1) << std::endl;
    std::cout << (vec > vec1) << std::endl;
    vec[1] = "5";
    std::cout << (vec != vec1) << std::endl;
    std::cout << (vec <= vec1) << std::endl;
    std::cout << (vec >= vec1) << std::endl;

  }


}

#endif //FT_CONTAINERS_TESTS_VECTORTESTS_HPP_
