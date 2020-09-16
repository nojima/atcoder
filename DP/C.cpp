#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N; cin >> N;
    vector H(N, vector(3, int()));
    REP(i, N) cin >> H[i][0] >> H[i][1] >> H[i][2];

    // dp[i][a]: i日目にaをするときの、i日目までの幸福度の総和の最大値
    vector dp(N, vector(3, int()));

    REP(a, 3) dp[0][a] = H[0][a];
    FOR(i, 1, N) REP(a, 3) {
        dp[i][a] = max(dp[i-1][(a+1)%3], dp[i-1][(a+2)%3]) + H[i][a];
    }

    cout << *max_element(ALL(dp[N-1])) << '\n';
}
