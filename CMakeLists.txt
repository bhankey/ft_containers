cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
include_directories(Containers Iterators)

add_executable(ft_containers main.cpp Containers/Vector.hpp Iterators/VectorIterator.hpp Iterators/iterator.hpp Iterators/Reverse_iterator.hpp)