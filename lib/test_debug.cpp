#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#include "debug.hpp"

int main() {
    auto p = make_pair(100, "hello");
    stringstream ss1;
    ss1 << p;
    assert(ss1.str() == "(100, hello)");

    vector<int> v = {1, 3, 5, 7, 9};
    stringstream ss2;
    ss2 << v;
    assert(ss2.str() == "[1, 3, 5, 7, 9]");

    cout << "OK" << endl;
}
