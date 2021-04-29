//
// Created by sergey on 18.04.2021.
//

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <list>
#include <stack>

#include "print.hpp"
#include "VectorTests.hpp"
#include "ListTests.hpp"
#include "MapTester.hpp"

int main() {
    TestVector<std::vector<std::string> >();
    TestList<std::list<std::string> >();
    return 0;
}