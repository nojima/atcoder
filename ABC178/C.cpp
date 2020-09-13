#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

static constexpr int64_t MOD = 1'000'000'007;

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
    int N; cin >> N;
    if (N < 2) {
        cout << 0 << endl;
        return 0;
    }
    // 作り方全体 10^N
    // 0 を使わずに作る作り方 9^N
    // 9 を使わずに作る作り方 9^N
    // 0も9も使わずに作る作り方 8^N
    int64_t ans = add_mod(sub_mod(pow_mod(10, N), mul_mod(2, pow_mod(9, N))), pow_mod(8, N));
    cout << ans << endl;
}
