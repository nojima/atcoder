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

// エラトステネスの篩
// O(n log log n)
vector<bool> sieve(int n) {
    vector<bool> is_prime(n, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < n; ++i) {
        for (int j = i + i; j < n; j += i) {
            is_prime[j] = false;
        }
    }
    return is_prime;
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
