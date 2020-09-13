#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N; cin >> N;
    vector<pair<int64_t, int64_t>> points(N);
    REP(i, N) cin >> points[i].first >> points[i].second;

    vector<vector<int64_t>> f(N);
    REP(i, N) {
        auto [x, y] = points[i];
        f[i] = {x-y, x+y};
    }

    int64_t ans = numeric_limits<int64_t>::min();
    REP(d, 2) {
        auto m1 = numeric_limits<int64_t>::max();
        auto m2 = numeric_limits<int64_t>::min();
        REP(i, N) m1 = min(m1, f[i][d]);
        REP(i, N) m2 = max(m2, f[i][d]);
        ans = max(ans, m2 - m1);
    }
    cout << ans << endl;
}
