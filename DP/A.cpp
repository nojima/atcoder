#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

template <typename T> inline void assign_min(T& x, const T& value) noexcept { x = min(x, value); }

int main() {
    int N; cin >> N;
    vector<int> h(N);
    REP(i, N) cin >> h[i];

    // dp[i]: i番目の足場につくまでに支払うコストの総和の最小値
    vector<int> dp(N);
    FOR(i, 1, N) {
        dp[i] = dp[i-1] + abs(h[i] - h[i-1]);
        if (i >= 2) assign_min(dp[i], dp[i-2] + abs(h[i] - h[i-2]));
    }

    cout << dp[N-1] << '\n';
}
