#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr int64_t INF = 1e12;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int N; cin >> N;
    int64_t W; cin >> W;
    vector<int64_t> ws(N);
    vector<int> vs(N);
    REP(i, N) cin >> ws[i] >> vs[i];

    int total_value = 0;
    REP(i, N) total_value += vs[i];

    // dp[i][v]: i番目までの品物を使って価値の合計をvにするときの重さの総和の最小値
    vector dp(N, vector(total_value+1, int64_t()));
    dp[0][0] = 0;
    FOR(v, 1, total_value+1) {
        dp[0][v] = (vs[0] == v) ? ws[0] : INF;
    }
    FOR(i, 1, N) REP(v, total_value+1) {
        dp[i][v] = dp[i-1][v];
        if (v-vs[i] >= 0) {
            dp[i][v] = min(dp[i][v], dp[i-1][v-vs[i]] + ws[i]);
        }
    }

    int ans = 0;
    REP(v, total_value+1) if (dp[N-1][v] <= W) {
        ans = v;
    }
    cout << ans << '\n';
}
