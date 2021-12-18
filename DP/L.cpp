#include "lib/prelude.hpp"

int main() {
    int N = read_int();
    vector<int64_t> A(N);
    REP(i, N) A[i] = read_int();

    // dp[n][l]:
    //   要素が今 n 個残っており、残っている要素の左端のインデックスが l である。
    //   この状態からスタートしたとき、手番のプレイヤーは何点勝ち越せるか？
    vector dp(N+1, vector(N, int64_t(0)));

    FOR(n, 1, N+1) {
        REP(l, N) {
            int r = l + n - 1;
            if (r >= N) { break; }
            // 右から取る
            auto score = A[r] - dp[n-1][l];
            if (l+1 < N) {
                // 左から取る
                assign_max(score, A[l] - dp[n-1][l+1]);
            }
            dp[n][l] = score;
        }
    }

    cout << dp[N][0] << LF;
}
