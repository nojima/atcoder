#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <optional>
using namespace std;

#include "monoid.hpp"

void test_monoid_pow() {
    assert(monoid_pow(1LL, 1) == 1LL);
    assert(monoid_pow(2LL, 20) == 1048576LL);
    assert(monoid_pow(2LL, 0) == 1LL);
}

void test_pair_monoid() {
    using M = Monoid<pair<int64_t, string>>;

    pair<int64_t, string> a = {100, "hello"};
    pair<int64_t, string> b = {200, " world"};

    assert(M::op(a, b) == make_pair(20000LL, string("hello world")));
    assert(M::identity() == make_pair(1LL, string("")));
}

void test_optional_monoid() {
    using M = Monoid<optional<int64_t>>;

    optional<int64_t> a = {100};
    optional<int64_t> b = {200};

    assert(M::op(a, b) == 20000);
    assert(M::op(a, nullopt) == a);
    assert(M::op(nullopt, a) == a);
    assert(M::op(nullopt, nullopt) == nullopt);
}

int main() {
    test_monoid_pow();
    test_pair_monoid();
    test_optional_monoid();
    cout << "OK" << endl;
}
