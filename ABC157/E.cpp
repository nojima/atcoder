#include "lib/prelude.hpp"
#include "lib/io/string.hpp"
#include "lib/io/char.hpp"
#include "lib/fenwick_tree.hpp"

int main() {
    int N = read_int();
    string S = read_word();
    int Q = read_int();

    REP(i, N) { S[i] -= 'a'; }

    // freq[c][i]: i文字目に文字cが出現するなら1、そうでないなら0
    vector freq(26, FenwickTree<int>(N));
    REP(i, N) { freq[S[i]].add(i, 1); }

    REP(q, Q) {
        int T = read_int();
        if (T == 1) {
            int i = read_int()-1;
            char c = read_char()-'a';
            freq[S[i]].add(i, -1);
            freq[c].add(i, 1);
            S[i] = c;
        } else {
            int l = read_int()-1;
            int r = read_int()-1;
            int ans = 0;
            REP(c, 26) {
                if (freq[c].sum(l, r) > 0) { ans++; }
            }
            cout << ans << LF;
        }
    }
}
