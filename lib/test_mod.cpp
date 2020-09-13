#include <iostream>
#include <cassert>
#include <random>
using namespace std;

#include "mod.hpp"

int main() {
    mt19937 rng(1234567890);

    vector<int64_t> as1 = {0, 1, 2, 1'000'000'007};
    for (int i = 0; i < 1000; ++i) {
        as1.push_back(rng() % 1'000'000'007);
    }
    for (auto a : as1) {
        for (auto b : as1) {
            auto [x, y] = exgcd(a, b);
            assert(a*x + b*y == gcd(a, b));
        }
    }

    vector<int64_t> as2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1000000006};
    for (int i = 0; i < 100000; ++i) {
        as2.push_back(rng() % 1000000006 + 1);
    }
    for (auto a : as2) {
        auto inv_a = inverse(a);
        assert(inv_a >= 0 && inv_a < MOD);
        assert(inv_a * a % MOD == 1);
    }

    cout << "OK" << endl;
}
