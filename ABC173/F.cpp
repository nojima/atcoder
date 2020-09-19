#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int64_t N; cin >> N;
    int64_t ans = 0;
    FOR(v, 1, N+1) {
        ans += v * (N - v + 1);
    }
    REP(i, N-1) {
        int v, w; cin >> v >> w;
        if (v > w) swap(v, w);
        ans -= v * (N - w + 1);
    }
    cout << ans << '\n';
}
