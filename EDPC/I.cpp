#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N; cin >> N;
    vector<double> ps(N);
    REP(i, N) cin >> ps[i];

    // dp[i][m]: i番目までのコインを投げたとき表がちょうどm個出る確率
    vector dp(N, vector(N+1, double()));
    dp[0][0] = 1.0 - ps[0];
    dp[0][1] = ps[0];
    FOR(i, 1, N) REP(m, N+1) {
        dp[i][m] = dp[i-1][m] * (1.0 - ps[i]);
        if (m > 0) dp[i][m] += dp[i-1][m-1] * ps[i];
    }

    double ans = 0;
    FOR(m, N/2+1, N+1) ans += dp[N-1][m];
    cout << fixed << setprecision(15) << ans << '\n';
}
