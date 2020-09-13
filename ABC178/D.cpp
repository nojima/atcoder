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

template <typename Int>
vector<int64_t> make_cumsum(const vector<Int>& v) {
    vector<int64_t> cumsum(v.size()+1);
    for (size_t i = 1; i < cumsum.size(); ++i) {
        cumsum[i] = add_mod(cumsum[i-1], v[i-1]);
    }
    return cumsum;
}

// [first, last] の和を返す
inline int64_t sum_of(const vector<int64_t>& cumsum, int first, int last) noexcept {
    return sub_mod(cumsum[last+1], cumsum[first]);
}

int main() {
    int S; cin >> S;
    int N = (S+2)/3;

    // dp[n][s]: n個の整数を使ってsを作る作り方の数
    vector dp(N+1, vector(S+1, int()));
    vector<vector<int64_t>> cumsum(N+1);

    dp[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
        cumsum[n-1] = make_cumsum(dp[n-1]);
        for (int s = 3; s <= S; ++s) {
            dp[n][s] = sum_of(cumsum[n-1], 0, s-3);
        }
    }

    int64_t ans = 0;
    REP(n, N+1) ans = add_mod(ans, dp[n][S]);
    cout << ans << endl;
}
