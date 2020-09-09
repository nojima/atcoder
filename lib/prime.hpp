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

// すべての約数に対して f(divisor) を呼び出す。1は約数に含まない。
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
