#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include "lib/fix.hpp"

using mint = ModInt<int(1e9 + 7)>;

enum Color { BLACK, WHITE };

int main() {
    int N = read_int();
    vector<vector<int>> edges(N);
    REP(i, N-1) {
        int x = read_int() - 1;
        int y = read_int() - 1;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    // dp(v, color):
    //   頂点 v を color で塗る。
    //   このときの v を根とするサブツリーの色の組み合わせ。
    vector dp(N, vector(2, optional<mint>(nullopt)));
    auto dfs = Fix([&](auto&& self, int v, Color color, int parent) -> mint {
        if (dp[v][color]) {
            return *dp[v][color];
        }

        mint c = 1;
        for (int w : edges[v]) {
            if (w == parent) { continue; }
            mint c_w = self(w, WHITE, v);
            if (color == WHITE) {
                c_w += self(w, BLACK, v);
            }
            c *= c_w;
        }

        dp[v][color] = c;
        return c;
    });

    mint ans = dfs(0, WHITE, -1) + dfs(0, BLACK, -1);
    cout << ans << LF;
}
