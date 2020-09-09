#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

// hi以下の素数を小さい順に返す
// O(hi^1.5)
vector<int> primes_under(int hi) {
    vector<int> primes;
    primes.push_back(2);
    for (int i = 3; i <= hi; i += 2) {
        bool ok = true;
        for (auto p : primes) {
            if (p*p > hi) { break; }
            if (i % p == 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            primes.push_back(i);
        }
    }
    return primes;
}

// nを素因数分解する
// 事前条件: primes は sqrt(n) 以下の素数をすべて含んでいなければならない
// O(sqrt(n))
vector<pair<int64_t, int>> prime_factorization(const vector<int>& primes, int64_t n) {
    vector<pair<int64_t, int>> factors;
    for (int64_t p : primes) {
        if (p*p > n) { break; }
        int cnt = 0;
        while (n % p == 0) {
            n /= p;
            ++cnt;
        }
        if (cnt > 0) {
            factors.push_back({p, cnt});
        }
    }
    if (n > 1) {
        factors.push_back({n, 1});
    }
    return factors;
}

template <class Func>
void foreach_divisor(const vector<pair<int64_t, int>>& factors, Func f, int i = 0, int64_t d = 1) {
    if (i == (int)factors.size()) {
        if (d != 1) {
            f(d);
        }
    } else {
        auto [factor, power] = factors[i];
        for (int k = 0; k <= power; ++k) {
            if (k != 0) { d *= factor; }
            foreach_divisor(factors, f, i+1, d);
        }
    }
}

int main() {
    int64_t N; cin >> N;

    const auto primes = primes_under((int64_t)sqrt(N) + 1);

    int64_t ans = 0;

    // NがKの倍数でないときの場合の数を求める
    {
        int64_t n = 1;
        for (auto [factor, power] : prime_factorization(primes, N-1)) {
            n *= power + 1;
        }
        ans += n - 1;
    }

    // NがKの倍数であるときの場合の数を求める
    {
        foreach_divisor(prime_factorization(primes, N), [N, &ans](int64_t d) {
            int64_t N_ = N;
            while (N_ % d == 0) { N_ /= d; }
            if ((N_ - 1) % d == 0) { ans++; }
        });
    }

    cout << ans << '\n';
}
