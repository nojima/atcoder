#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

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

int main() {
    int N, K; cin >> N >> K;

    // g(i): gcd(A_1,..,A_N) = i となるような {A_1,..,A_N} の数
    vector<int64_t> g(K+1);

    for (int i = K; i > 0; --i) {
        int64_t k = pow_mod(K/i, N);
        for (int j = 2; i*j <= K; ++j) {
            k = sub_mod(k, g[i*j]);
        }
        g[i] = k;
    }

    int64_t ans = 0;
    for (int i = 1; i <= K; ++i) {
        ans = add_mod(ans, mul_mod(g[i], i));
    }
    cout << ans << '\n';
}
