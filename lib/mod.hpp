static const int64_t MOD = 1'000'000'007;

inline int64_t add_mod(int64_t a, int64_t b) { return (a + b) % MOD; }
inline int64_t sub_mod(int64_t a, int64_t b) { return (a - b + MOD) % MOD; }
inline int64_t mul_mod(int64_t a, int64_t b) { return (a * b) % MOD; }

int64_t pow_mod(int64_t n, int64_t p) {
    n %= MOD;
    int64_t ans = 1;
    while (p > 0) {
        if (p & 1) {
            ans = mul_mod(ans, n);
        }
        n = mul_mod(n, n);
        p >>= 1;
    }
    return ans;
}
