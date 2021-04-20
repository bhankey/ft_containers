//
// Created by sergey on 20.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_LISTNODE_HPP_
#define FT_CONTAINERS_CONTAINERS_LISTNODE_HPP_

namespace ft {

struct List_basic_node {
  List_basic_node *prev;
  List_basic_node *next;
};

template<typename T>
struct List_node : public List_basic_node {
  T data;
};

}

#endif //FT_CONTAINERS_CONTAINERS_LISTNODE_HPP_
