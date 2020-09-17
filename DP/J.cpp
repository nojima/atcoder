#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N; cin >> N;
    vector<int> a(N);
    REP(i, N) cin >> a[i];

    // dp[c3][c2][c1]: 寿司が1個,2個,3個の皿がそれぞれc1,c2,c3個あるときの期待値
    // dp[c3][c2][c1] =
    //   (c1 / N) * (dp[c3][c2][c1-1] + 1) +
    //   (c2 / N) * (dp[c3][c2-1][c1+1] + 1) +
    //   (c3 / N) * (dp[c3-1][c2+1][c1] + 1) +
    //   ((N-c1-c2-c3)/N) * (dp[c3][c2][c1] + 1)
    // ∴ (1 - (N-c1-c2-c3)/N) dp[c3][c2][c1] = (c1 / N) * ... + (N-c1-c2-c3)/N
    // ∴ dp[c3][c2][c1] = N / (c1+c2+c3) * { (c1 / N) * ... + (N-c1-c2-c3)/N }
    vector dp(N+1, vector(N+1, vector(N+1, double())));

    REP(c3, N+1) REP(c2, N+1) REP(c1, N+1) {
        if (c1+c2+c3 == 0) continue;
        if (c1+c2+c3 > N) continue;
        double E = double(N-c1-c2-c3) / N;
        if (c1 > 0) E += ((double)c1 / N) * (dp[c3][c2][c1-1] + 1);
        if (c2 > 0) E += ((double)c2 / N) * (dp[c3][c2-1][c1+1] + 1);
        if (c3 > 0) E += ((double)c3 / N) * (dp[c3-1][c2+1][c1] + 1);
        dp[c3][c2][c1] = ((double)N / (c1+c2+c3)) * E;
    }

    int c[3] = {};
    REP(i, N) c[a[i]-1]++;
    cout << fixed << setprecision(15) << dp[c[2]][c[1]][c[0]] << '\n';
}
