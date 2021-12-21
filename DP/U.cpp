#include "lib/prelude.hpp"
#include "lib/bit_set.hpp"

int main() {
    int N = read_int();
    vector A(N, vector(N, int64_t(0)));
    REP(i, N) REP(j, N) {
        A[i][j] = read_int();
    }

    // score[S]: Sに属するうさぎを同じグループに入れたときの得点
    vector score(1<<N, int64_t(0));
    foreach_subset(N, [&](BitSet S) {
        S.foreach_element([&](int i) {
            S.foreach_element([&](int j) {
                if (i < j) {
                    score[S.raw()] += A[i][j];
                }
            });
        });
    });

    // dp[S]: Sに属するうさぎをグループ分けする。このときの得点の最大値。
    vector dp(1<<N, numeric_limits<int64_t>::min() / 10);
    foreach_subset(N, [&](BitSet S) {
        if (S == BitSet::empty()) {
            dp[S.raw()] = 0;
        } else {
            S.foreach_subset([&](BitSet T) {
                if (T != BitSet::empty()) {
                    assign_max(dp[S.raw()], dp[S.exclude(T).raw()] + score[T.raw()]);
                }
            });
        }
    });

    cout << dp[(1<<N)-1] << LF;
}
