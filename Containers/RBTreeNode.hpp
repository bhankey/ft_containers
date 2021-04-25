//
// Created by sergey on 22.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_RBTREENODE_HPP_
#define FT_CONTAINERS_CONTAINERS_RBTREENODE_HPP_

#include <cstddef>

namespace ft {

  enum RB_tree_color {
    red = false,
    black = true
  };

template<typename T>
struct RB_tree_node {
  RB_tree_color     color;
  RB_tree_node		*parent;
  RB_tree_node		*left;
  RB_tree_node		*right;

  T data;

  T *value_ptr() {
    return &data;
  }
  const T *const_value_ptr() {
    return &data;
  }
};

}

#endif //FT_CONTAINERS_CONTAINERS_RBTREENODE_HPP_
