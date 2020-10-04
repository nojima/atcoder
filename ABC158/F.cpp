#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include "lib/fix.hpp"

using mint = ModInt<998244353>;

struct Robot {
    int64_t id, x, d;
};

int main() {
    int N = read_int();
    vector<Robot> robots(N);
    REP(i, N) {
        robots[i].x = read_int();
        robots[i].d = read_int();
    }

    sort(ALL(robots), [](auto a, auto b){
        return a.x < b.x;
    });
    REP(i, N) { robots[i].id = i; }

    vector<vector<int>> forest(N);
    deque<Robot> Q;
    for (int i = N-1; i >= 0; --i) {
        auto r0 = robots[i];
        while (!Q.empty()) {
            auto r = Q.front();
            if (r0.x + r0.d <= r.x) { break; }
            Q.pop_front();
            forest[i].emplace_back(r.id);
        }
        Q.push_front(r0);
    }

    auto dp = Fix([&](auto&& self, int v) -> mint {
        mint ret(1);
        for (int w : forest[v]) {
            ret *= self(w);
        }
        ret += 1;
        return ret;
    });

    mint ans(1);
    while (!Q.empty()) {
        ans *= dp(Q.front().id);
        Q.pop_front();
    }
    cout << ans << LF;
}
