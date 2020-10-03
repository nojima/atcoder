#include "lib/prelude.hpp"
#include "lib/modint.hpp"

using mint = ModInt<998244353>;

int main() {
    auto N = read_int();
    auto S = read_int();
    vector<int> A(N);
    REP(i, N) A[i] = read_int();

    vector dp(N, vector(S+1, mint()));
    dp[0][0] = 2;
    if (A[0] <= S) dp[0][A[0]] = 1;
    FOR(i, 1, N) {
        REP(s, S+1) {
            dp[i][s] = dp[i-1][s] * 2;
            if (s-A[i] >= 0) dp[i][s] += dp[i-1][s-A[i]];
        }
    }
    cout << dp[N-1][S] << LF;
}
