#include <algorithm>
using namespace std;

static constexpr int64_t MOD = 1000000007;

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

// 以下を満たすような (x, y) を返す。
//   ax + by = gcd(a, b)
pair<int64_t, int64_t> exgcd(int64_t a, int64_t b) noexcept {
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a%b);
    return {y, x-(a/b)*y};
}

// a の逆元(>=0)を返す。a は MOD と互いに素でなければならない。
inline int64_t inverse(int64_t a) noexcept {
    auto x = exgcd(MOD, a).second % MOD;
    return x < 0 ? x + MOD : x;
}
