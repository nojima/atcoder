#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <optional>
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
    using M = PairMonoid<ProductMonoid, StringMonoid>;

    pair<long long, string> a = {100, "hello"};
    pair<long long, string> b = {200, " world"};

    assert(M::op(a, b) == make_pair(20000LL, string("hello world")));
    assert(M::identity() == make_pair(1LL, string("")));
}

void test_optional_monoid() {
    using M = OptionalMonoid<SumMonoid>;

    optional<long long> a = {100};
    optional<long long> b = {200};

    assert(M::op(a, b) == 300);
    assert(M::op(a, nullopt) == a);
    assert(M::op(nullopt, a) == a);
    assert(M::op(nullopt, nullopt) == nullopt);
}

void test_cumulative() {
    using M = SumMonoid;

    auto v1 = cumulative<M>({});
    assert(v1.empty());

    auto v2 = cumulative<M>({1, 2, 3});
    auto e2 = vector<long long>({1, 3, 6});
    assert(v2 == e2);
}

int main() {
    test_monoid_pow();
    test_pair_monoid();
    test_optional_monoid();
    test_cumulative();
    cout << "OK" << endl;
}
