#include <iostream>
#include <cassert>
using namespace std;

#include "monoid.hpp"

template <>
struct MonoidTrait<long long> {
    static const long long MOD = 1000000007;

    static long long identity() {
        return 1;
    }

    static int op(long long lhs, long long rhs) {
        return (lhs * rhs) % MOD;
    }
};

void test_monoid_pow() {
    assert(monoid_pow(1LL, 1) == 1LL);
    assert(monoid_pow(2LL, 20) == 1048576LL);
    assert(monoid_pow(3LL, 10000) == 895629451LL);
    assert(monoid_pow(2LL, 0) == 1LL);
}

int main() {
    test_monoid_pow();
    cout << "OK" << endl;
}
