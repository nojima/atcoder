#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include "lib/debug.hpp"

using mint = ModInt<int(1e9+7)>;

int main() {
    int N = read_int();
    int K = read_int();
    vector<int> A(N);
    REP(i, N) A[i] = read_int();

    // dp(n, k):
    //   n番目までの子供たちにk個の飴を配る場合の数
    vector dp(N, vector(K+1, mint(0)));

    REP(k, K+1) { dp[0][k] = (k <= A[0]) ? 1 : 0; }
    FOR(n, 1, N) {
        dp[n][0] = 1;
        FOR(k, 1, K+1) {
            dp[n][k] = dp[n][k-1] + dp[n-1][k];
            if (k-A[n]-1 >= 0) {
                dp[n][k] -= dp[n-1][k-A[n]-1];
            }
            //clog << TAGGED(n) << TAGGED(k) << TAGGED(dp[n][k]) << LF;
        }
    }

    cout << dp[N-1][K] << LF;
}
