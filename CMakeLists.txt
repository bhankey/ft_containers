cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
include_directories(Containers Iterators FunctionsForTest ./)
#tests/main_std.cpp tests/main.cpp
add_executable(ft_containers tests/main.cpp  Containers/Vector.hpp Iterators/VectorIterator.hpp Iterators/ReverseIterator.hpp tests/print.hpp  tests/VectorTests.hpp Containers/List.hpp Iterators/ListIterator.hpp Containers/ListNode.hpp Containers/Map.hpp Containers/RBTree.hpp Containers/RBTreeNode.hpp Iterators/RBTreeIterator.hpp tests/ListTests.hpp Containers/Stack.hpp Containers/Queue.hpp tests/MapTester.hpp Containers/Multimap.hpp tests/MultimapTests.hpp Containers/Set.hpp tests/SetTests.hpp "Containers/Multiset.hpp" tests/MultisetTests.hpp)