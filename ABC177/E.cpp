#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

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
vector<pair<int, int>> prime_factorization(const vector<int>& primes, int n) {
    vector<pair<int, int>> factors;
    for (auto p : primes) {
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

bool is_pairwise_coprime(
    int N, const vector<int>& A, const vector<int>& primes
) {
    unordered_set<int> used_factors;
    REP(i, N) {
        auto factors = prime_factorization(primes, A[i]);
        for (auto f : factors) {
            if (used_factors.find(f.first) != used_factors.end()) {
                return false;
            }
            used_factors.insert(f.first);
        }
    }
    return true;
}

bool is_setwise_coprime(
    int N, const vector<int>& A
) {
    int g = gcd(A[0], A[1]);
    for (int i = 2; i < N; ++i) {
        g = gcd(g, A[i]);
    }
    return g == 1;
}

int main() {
    int N; cin >> N;
    vector<int> A(N);
    REP(i, N) cin >> A[i];

    const auto primes = primes_under(1000);

    if (is_pairwise_coprime(N, A, primes)) {
        cout << "pairwise coprime\n";
    } else if (is_setwise_coprime(N, A)) {
        cout << "setwise coprime\n";
    } else {
        cout << "not coprime\n";
    }
}
