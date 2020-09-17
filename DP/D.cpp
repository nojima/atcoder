#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N, W; cin >> N >> W;
    vector<int> ws(N);
    vector<int64_t> vs(N);
    REP(i, N) cin >> ws[i] >> vs[i];

    // dp[i][w]: i番目までの品物を使える。重さの総和はw以下にする。このときの価値の総和の最大値
    vector dp(N, vector(W+1, int64_t()));
    REP(w, W+1) dp[0][w] = (w - ws[0] >= 0) ? vs[0] : 0;
    FOR(i, 1, N) REP(w, W+1) {
        dp[i][w] = dp[i-1][w];
        if (w - ws[i] >= 0) {
            dp[i][w] = max(dp[i][w], dp[i-1][w - ws[i]] + vs[i]);
        }
    }

    cout << dp[N-1][W] << '\n';
}
