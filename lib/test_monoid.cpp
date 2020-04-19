#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "monoid.hpp"

void test_monoid_pow() {
    using M = ModuloProductMonoid;
    assert(monoid_pow<M>(1LL, 1) == 1LL);
    assert(monoid_pow<M>(2LL, 20) == 1048576LL);
    assert(monoid_pow<M>(3LL, 10000) == 895629451LL);
    assert(monoid_pow<M>(2LL, 0) == 1LL);
}

void test_pair_monoid() {
    using M = PairMonoid<ModuloProductMonoid, StringMonoid>;

    pair<long long, string> a = {100, "hello"};
    pair<long long, string> b = {200, " world"};

    assert(M::op(a, b) == make_pair(20000LL, string("hello world")));
    assert(M::identity() == make_pair(1LL, string("")));
}

int main() {
    test_monoid_pow();
    test_pair_monoid();
    cout << "OK" << endl;
}
