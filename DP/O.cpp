#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include "lib/bit_set.hpp"

using mint = ModInt<int(1e9+7)>;

int main() {
    int N = read_int();
    vector affinity(N, vector(N, false));
    REP(i, N) REP(j, N) affinity[i][j] = (bool)read_int();

    // dp(i, S):
    //   i番目までの男性を全員マッチさせる。
    //   集合Sに属する女性のみがマッチ可能。
    //   このときの組み合わせの数。
    vector dp(N, vector(1<<N, mint(0)));

    REP(i, N) {
        foreach_power_set(N, [&](BitSet S) {
            if (S.size() == i+1) {
                mint c = 0;
                REP(j, N) if(S[j] && affinity[i][j]) {
                    // i と j でマッチさせる
                    c += (i == 0) ? 1 : dp[i-1][S.exclude(j).data];
                }
                dp[i][S.data] = c;
            }
        });
    }

    cout << dp[N-1][(1<<N)-1] << LF;
}
