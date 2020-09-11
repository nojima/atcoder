#include <iostream>
#include <cassert>
using namespace std;

#include "utility.hpp"

int main() {
    vector v = {1, 5, -2, 3, 7};
    auto cumsum = make_cumsum(v);

    assert(sum_of(cumsum, 1, 2) == 5);
    assert(sum_of(cumsum, 0, 5) == 14);
    assert(sum_of(cumsum, 1, 4) == 6);
    assert(sum_of(cumsum, 5, 5) == 0);

    cout << "OK" << endl;
}
