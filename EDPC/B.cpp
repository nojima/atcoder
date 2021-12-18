#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

template <typename T> inline void assign_min(T& x, const T& value) noexcept { x = min(x, value); }

int main() {
    int N, K; cin >> N >> K;
    vector<int> h(N);
    REP(i, N) cin >> h[i];

    // dp[i]: i番目の足場に辿り着くまでに支払うコストの総和の最小値
    vector<int> dp(N);
    FOR(i, 1, N) {
        dp[i] = numeric_limits<int>::max();
        FOR(k, 1, K+1) {
            if (i-k < 0) break;
            assign_min(dp[i], dp[i-k] + abs(h[i] - h[i-k]));
        }
    }

    cout << dp[N-1] << '\n';
}
