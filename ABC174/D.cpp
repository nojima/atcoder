#include "lib/prelude.hpp"
#include "lib/io/char.hpp"

int main() {
    int N = read_int();
    vector<char> C(N);
    REP(i, N) C[i] = read_char();

    int total_w = 0, total_r = 0;
    REP(i, N) {
        if (C[i] == 'W')
            ++total_w;
        else
            ++total_r;
    }

    // 0~iをすべてRにし、i+1~N-1をWにしたい
    // max(前半のWの数, 後半のRの数)
    auto ans = min(total_w, total_r);
    int n_w = 0, n_r = 0;
    REP(i, N) {
        if (C[i] == 'W')
            ++n_w;
        else
            ++n_r;
        assign_min(ans, max(n_w, total_r - n_r));
    }
    cout << ans << LF;
}
