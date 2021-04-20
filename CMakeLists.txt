cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
include_directories(Containers Iterators FunctionsForTest ./)
#tests/main_std.cpp
add_executable(ft_containers tests/main.cpp Containers/Vector.hpp Iterators/VectorIterator.hpp Iterators/ReverseIterator.hpp tests/print.hpp  tests/VectorTests.hpp Containers/List.hpp Iterators/ListIterator.hpp Containers/ListNode.hpp)