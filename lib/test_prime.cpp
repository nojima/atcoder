#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

#include "prime.hpp"

void test_primes_under() {
    auto primes = primes_under(100);
    vector<int> expected = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
    };
    assert(primes == expected);
}

void test_sieve() {
    auto is_prime = sieve(1000);
    auto primes = primes_under(1000);

    for (int n = 0; n < 1000; ++n) {
        auto it = find(primes.begin(), primes.end(), n);
        auto b1 = it != primes.end();
        auto b2 = is_prime[n];
        assert(b1 == b2);
    }
}

void test_prime_factorization() {
    auto primes = primes_under(1000);

    vector<pair<int, int>> expected1 = {{2, 1}};
    assert(prime_factorization(primes, 2) == expected1);

    vector<pair<int, int>> expected2 = {{3, 2}};
    assert(prime_factorization(primes, 9) == expected2);

    vector<pair<int, int>> expected3 = {{2, 1}, {5, 1}};
    assert(prime_factorization(primes, 10) == expected3);

    vector<pair<int, int>> expected4 = {{997, 2}};
    assert(prime_factorization(primes, 994009) == expected4);

    vector<pair<int, int>> expected5 = {{999983, 1}};
    assert(prime_factorization(primes, 999983) == expected5);

    vector<pair<int, int>> expected6 = {{2, 10}};
    assert(prime_factorization(primes, 1024) == expected6);

    vector<pair<int, int>> expected7 = {{2, 1}, {3, 1}, {5, 1}, {7, 1}};
    assert(prime_factorization(primes, 210) == expected7);
}

int main() {
    test_primes_under();
    test_sieve();
    test_prime_factorization();
    cout << "OK" << endl;
}
