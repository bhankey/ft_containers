//
// Created by sergey on 22.04.2021.
//

#ifndef FT_CONTAINERS_TESTS_LISTTESTS_HPP_
#define FT_CONTAINERS_TESTS_LISTTESTS_HPP_

#include "print.hpp"

template<typename List>
void PrintListInfo(List l) {
  std::cout << "list size: " << l.size() << " max_size: " << l.max_size() << std::endl;
  if (!l.empty()) {
   std::cout << "back: " << l.back() << " front: " << l.front() << std::endl;
  }
}

template<typename T>
bool return_true(T &a) {
  static_cast<void>(a);
  return true;
}

template<typename List>
void TestList() {
  std::cout << "List Test" << std::endl;
  std::cout << "Testing constructors, operation '=' and assign" << std::endl;
  List full(100, "full");
  {
    List a;
    a.push_back("daw");
    a.push_back("aw");
    const List b(a);
    typename List::iterator it = a.erase(a.begin());
    std::cout << *it;
    PrintListInfo(a);
    printByAlgorithms(a);
    PrintListInfo(b);
    printByAlgorithmsReverse(b);
  }
  {
    List a(full.begin(), full.end());
    PrintListInfo(a);
    printByAlgorithms(a);
  }
  {
    List a(full);
    PrintListInfo(a);
    printByAlgorithms(a);
    a.clear();
    PrintListInfo(a);
    printByAlgorithms(a);
  }
  {
    List a(100);
    TestCompare(a, full);
    *(++a.begin()) = "lol";
    PrintListInfo(a);
    printByAlgorithms(a);
    List b(101);
    b.front() = "1";
    b = a;
    PrintListInfo(b);
    printByAlgorithms(b);
    b.push_back("a");
    a.assign(b.begin(), b.end());
    std::cout << (a == b) << std::endl;
    PrintListInfo(a);
    printByAlgorithms(a);
    PrintListInfo(b);
    printByAlgorithms(b);
    a.assign(b.begin(), b.begin());
    PrintListInfo(a);
    printByAlgorithms(a);
  }
  std::cout << "Modifiers and operations" << std::endl;
  {
   List a;
    a.push_back("1");
    a.push_back("6");
    a.push_back("11");
    List b;
    b.push_back("3");
    b.push_back("5");
    b.push_back("21");
    PrintListInfo(a);
    PrintListInfo(b);
    b.insert(b.begin(), "f");
    b.insert(--b.end(), "f");
    a.sort();
    b.insert(b.end(), a.begin(), a.end());
    printByAlgorithms(b);
    b.reverse();
    printByAlgorithms(b);
    a.splice(a.end(), b);
    PrintListInfo(a);
    PrintListInfo(b);
    printByAlgorithms(a);
    a.reverse();
    printByAlgorithms(a);
    a.pop_back();
    a.reverse();
    printByAlgorithms(a);
    a.pop_back();
    a.reverse();
    printByAlgorithms(a);
    a.pop_back();
    a.reverse();
    printByAlgorithms(a);
    a.pop_back();
    a.pop_front();
    PrintListInfo(a);
    PrintListInfo(b);
    TestCompare(a, b);
    List not_unique;
    for (int i = 0; i < 121; ++i) {
      not_unique.push_back("bbb");
    }
    for (int i = 0; i < 121; ++i) {
      not_unique.push_back("aaa");
    }
    for (int i = 0; i < 121; ++i) {
      not_unique.push_front("ccc");
    }
    PrintListInfo(not_unique);
    printByAlgorithmsReverse(not_unique);
    printByAlgorithms(not_unique);
    not_unique.sort();
    PrintListInfo(not_unique);
    printByAlgorithms(not_unique);
    not_unique.unique();
    printByAlgorithms(not_unique);
    printByAlgorithmsReverse(not_unique);
    PrintListInfo(not_unique);
    TestCompare(not_unique, a);
    TestCompare(not_unique, b);
    not_unique.clear();
    printByAlgorithms(not_unique);
    PrintListInfo(not_unique);
    TestCompare(not_unique, a);
    TestCompare(not_unique, b);
  }
  {
    List a(200);
    for (typename List::iterator it = a.begin(); it != a.end(); ++it) {
      *it = "adwdaw";
    }
    a.insert(++a.begin(), "second");
    a.insert(--a.end(), "secondFromEnd");
    List b(10);
    for (typename List::iterator it = b.begin(); it != b.end(); ++it) {
      *it = "b";
    }
    TestCompare(a, b);
    a.insert(a.begin(), b.begin(), b.end());
    a.insert(a.end(), b.begin(), b.end());
    PrintListInfo(a);
    printByAlgorithms(a);
    a.erase(a.begin(), ++++++++a.begin());
    a.erase(--a.end());
    PrintListInfo(a);
    printByAlgorithms(a);
    for (size_t i = 0; i < 10; ++i) {
      a.pop_back();
      a.pop_front();
      a.push_front("al");
    }
    PrintListInfo(a);
    printByAlgorithms(a);
    a.resize(5);
    PrintListInfo(a);
    printByAlgorithms(a);
    a.resize(100);
    PrintListInfo(a);
    printByAlgorithms(a);
    List sw;
    sw.push_back("aa");
    sw.swap(a);
    PrintListInfo(a);
    printByAlgorithms(a);
    PrintListInfo(sw);
    printByAlgorithms(sw);
    a.swap(sw);
    a.resize(1);
    a.pop_front();
    PrintListInfo(a);
    printByAlgorithms(a);
  }
  {
    List a;
    List b;
    a.swap(b);
    TestCompare(a, b);
    a.insert(a.begin(), 10, "aaa");
    PrintListInfo(a);
    printByAlgorithms(a);
  }
  {
    List a(200);
    for (typename List::iterator it = a.begin(); it != a.end(); ++it) {
      *it = "qwe";
    }
    List b(10);
    for (typename List::iterator it = b.begin(); it != b.end(); ++it) {
      *it = "b";
    }
    typename List::iterator it = a.begin();
    b.merge(a);
    std::cout << *it;
    for (;it != b.end(); ++it) {
      std::cout << *it << " ";
    }
    printByAlgorithms(b);
    PrintListInfo(b);
    PrintListInfo(a);
    std::cout << std::endl;
    it = ++(b.begin());
    a.splice(a.begin(), b);
    for (;it != a.end(); ++it) {
      std::cout << *it << " ";
    }
    printByAlgorithms(a);
    printByAlgorithms(b);
    PrintListInfo(a);
    PrintListInfo(b);
    TestCompare(a, b);
    a.remove("qwe");
    PrintListInfo(a);
    printByAlgorithms(a);
    a.assign(full.begin(), full.end());
    PrintListInfo(a);
    printByAlgorithms(a);
    a.remove("full");
    PrintListInfo(a);
    printByAlgorithms(a);
    List c(full);
    a.splice(a.begin(), c, ++c.begin());
    PrintListInfo(a);
    printByAlgorithms(a);
    a.splice(a.begin(), c, ++c.begin(), --c.end());
    PrintListInfo(a);
    printByAlgorithms(a);
    a.remove_if(return_true<typename List::value_type>);
    PrintListInfo(a);
    printByAlgorithms(a);
  }
  std::cout << "Test cases of List ended. Compare results with std" << std::endl;
}
#endif //FT_CONTAINERS_TESTS_LISTTESTS_HPP_
