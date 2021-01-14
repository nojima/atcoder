#include "lib/prelude.hpp"

int main() {
    int N = read_int();
    int M = read_int();
    vector<int64_t> A(N);
    vector<vector<int>> edges(N);
    REP(i, N) A[i] = read_int();
    REP(i, M) {
        int x = read_int() - 1;
        int y = read_int() - 1;
        edges[x].push_back(y);
    }

    // dp[i]: 街 i に持ち込める金の最低価格
    vector<int64_t> dp(N, 2e9);
    REP(v, N) {
        int64_t w = min(dp[v], A[v]);
        for(int dst : edges[v]) {
            dp[dst] = min(dp[dst], w);
        }
    }

    int64_t ans = -2e9;
    REP(v, N) {
        ans = max(ans, A[v] - dp[v]);
    }

    cout << ans << endl;
}
