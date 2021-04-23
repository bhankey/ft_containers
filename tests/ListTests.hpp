//
// Created by sergey on 22.04.2021.
//

#ifndef FT_CONTAINERS_TESTS_LISTTESTS_HPP_
#define FT_CONTAINERS_TESTS_LISTTESTS_HPP_

template<typename List>
void PrintListInfo(List l) {
  std::cout << "list size: " << l.size() << " max_size: " << l.max_size() << std::endl;
  if (!l.empty()) {
   std::cout << "back: " << l.back() << " front: " << l.front() << std::endl;
  }
}

template<typename List>
void TestList() {
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
    ft::List<std::string> not_unique;
    for (int i = 0; i < 109021; ++i) {
      not_unique.push_back("bbb");
    }
    for (int i = 0; i < 10221; ++i) {
      not_unique.push_back("aaa");
    }
    for (int i = 0; i < 1221; ++i) {
      not_unique.push_back("ccc");
    }
    PrintListInfo(not_unique);
    printByAlgorithms(not_unique);
    not_unique.sort();
    PrintListInfo(not_unique);
    printByAlgorithms(not_unique);
    not_unique.unique();
    printByAlgorithms(not_unique);
    PrintListInfo(not_unique);
  }
}
#endif //FT_CONTAINERS_TESTS_LISTTESTS_HPP_
