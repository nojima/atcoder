#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int N, X, Y; cin >> N >> X >> Y; --X; --Y;

    vector<int> ans(N);
    REP(i, N) FOR(j, i+1, N) {
        int dist = j - i;
        dist = min(dist, abs(i - X) + 1 + abs(j - Y));
        dist = min(dist, abs(i - Y) + 1 + abs(j - X));
        ++ans[dist];
    }
    FOR(i, 1, N) cout << ans[i] << '\n';
}
