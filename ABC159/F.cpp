#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

static const int64_t MOD = 998244353;

int main() {
    int N, S; cin >> N >> S;
    vector<int> A(N);
    REP(i, N) cin >> A[i];

    // 条件を満たす組(L, R, {x_i})を数え上げる。
    // dp[i][s][0]: 0..i のみを使うとき和がsになるような(L, {x_i})の数
    // dp[i][s][1]: 0..i のみを使うとき和がsになるような(L, R, {x_i})の数
    vector dp(N, vector(S+1, vector(2, int64_t())));
    REP(i, N) REP(s, S+1) {
        // A[i] を使わない場合
        dp[i][s][0] = (i>0 ? dp[i-1][s][0] : 0) + (s == 0);
        dp[i][s][1] = (i>0 ? dp[i-1][s][1] : 0) + dp[i][s][0] + (s == 0);
        // A[i] を使う場合
        if (s-A[i] >= 0) {
            dp[i][s][0] += (i>0 ? dp[i-1][s-A[i]][0] : 0) + (s-A[i] == 0);
            dp[i][s][1] += (i>0 ? dp[i-1][s-A[i]][0] : 0) + (s-A[i] == 0);
        }
        dp[i][s][0] %= MOD;
        dp[i][s][1] %= MOD;
    }
    cout << dp[N-1][S][1] << '\n';
}
