#include "lib/prelude.hpp"

int main() {
    int N = read_int();
    int K = read_int();
    vector<int> A(N);
    REP(i, N) A[i] = read_int();

    // dp[k]: 山にk個石があるとき、手番のプレイヤーの勝ちか？
    vector<bool> dp(K+1);

    REP(k, K+1) {
        // 後退解析: 遷移先の状態がすべて勝ちである場合、負け。そうでないなら勝ち。
        bool all_win = true;
        bool can_move = false;
        for (int a : A) if (k-a >= 0) {
            can_move = true;
            if (!dp[k-a]) { all_win = false; }
        }
        dp[k] = can_move && !all_win;
    }

    if (dp[K]) {
        cout << "First" << LF;
    } else {
        cout << "Second" << LF;
    }
}
