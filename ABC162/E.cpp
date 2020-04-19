#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

const long long MOD = 1000000007;

long long pow_mod(long long n, long long p) {
    n %= MOD;
    long long ans = 1;
    while (p > 0) {
        if (p & 1) {
            ans = (ans * n) % MOD;
        }
        n = (n * n) % MOD;
        p >>= 1;
    }
    return ans;
}

long long sub_mod(long long a, long long b) {
    return (a - b + MOD) % MOD;
}

int main() {
    vector<int> primes;
    primes.push_back(2);
    for (int i = 3; i < 100000; i += 2) {
        bool ok = true;
        for (int j = 0; primes[j]*primes[j] <= i; ++j) {
            if (i % primes[j] == 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            primes.push_back(i);
        }
    }

    long long N; cin >> N;
    long long K; cin >> K;

    long long S = 0;
    for (int g = 1; g <= K; ++g) {
        // gcd の結果が g になるような場合の数を数え上げる
        S = (S + pow_mod(K/g, N)) % MOD;

        // 素因数分解
        vector<int> factors;
        for (int p : primes) {
            if (p*p > g) {
                break;
            }
            while (g % p == 0) {
                factors.push_back(p);
                g /= p;
            }
        }

        for (int f : factors) {
            S = sub_mod(S, pow_mod())
        }
    }

    return 0;
}
