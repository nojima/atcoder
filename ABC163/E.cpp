#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N; cin >> N;
    vector<int64_t> A(N);
    REP(i, N) cin >> A[i];

    vector<pair<int64_t, int>> indexed(N);
    REP(i, N) indexed[i] = {A[i], i};
    sort(ALL(indexed), greater<pair<int, int>>());

    // dp[L][R] = 左にL人、右にR人配置したときの嬉しさの最大値
    vector<vector<int64_t>> dp(N+1, vector<int64_t>(N+1));
    REP(L, N+1) REP(R, N-L+1) {
        if (L == 0 && R == 0) {
            dp[L][R] = 0;
        } else {
            auto [_, k] = indexed[L+R-1];
            int64_t vl = L >= 1 ? dp[L-1][R] + A[k] * abs(k+1 - L)
                                : numeric_limits<int64_t>::min();
            int64_t vr = R >= 1 ? dp[L][R-1] + A[k] * abs(k+1 - (N-R+1))
                                : numeric_limits<int64_t>::min();
            dp[L][R] = max(vl, vr);
        }
    }

    int64_t ans = numeric_limits<int64_t>::min();
    REP(L, N+1) ans = max(ans, dp[L][N-L]);
    cout << ans << '\n';
}
