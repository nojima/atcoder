#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

template <class Func>
struct Fix {
    Func f;
    template <class... Args>
    decltype(auto) operator()(Args&&... args) const {
        return f(*this, forward<Args>(args)...);
    }
};
template <class Func>
Fix<std::decay_t<Func>> fix(Func&& f) {
    return {forward<Func>(f)};
}

using Graph = vector<vector<int>>;

int main() {
    int N, M; cin >> N >> M;
    Graph G(N);
    REP(i, M) {
        int x, y; cin >> x >> y; --x; --y;
        G[x].emplace_back(y);
    }

    // dp[v]: vから始まる有向パスの長さの最大値
    vector dp(N, int());
    vector visited(N, false);

    auto dfs = fix([&](auto&& self, int v) -> void {
        if (visited[v]) return;
        visited[v] = true;

        for(int child : G[v]) {
            self(child);
            dp[v] = max(dp[v], dp[child] + 1);
        }
    });
    REP(v, N) dfs(v);

    int ans = 0;
    REP(v, N) ans = max(ans, dp[v]);
    cout << ans << '\n';
}
