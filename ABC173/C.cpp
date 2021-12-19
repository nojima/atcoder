#include "lib/prelude.hpp"
#include "lib/io/string.hpp"
#include "lib/bit_set.hpp"

int main() {
    int H = read_int();
    int W = read_int();
    int K = read_int();
    vector<string> field(H);
    REP(i, H) { field[i] = read_word(); }

    int ans = 0;
    foreach_subset(H, [&](BitSet S){
        foreach_subset(W, [&](BitSet T){
            int c = 0;
            REP(y, H) if (S[y]) {
                REP(x, W) if (T[x]) {
                    if (field[y][x] == '#') { ++c; }
                }
            }
            if (c == K) { ++ans; }
        });
    });
    cout << ans << LF;
}
