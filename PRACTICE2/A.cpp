#include "lib/prelude.hpp"
#include <atcoder/dsu.hpp>

int main() {
    int N = read_int();
    int Q = read_int();

    atcoder::dsu d(N);
    REP(q, Q) {
        int t = read_int();
        int u = read_int();
        int v = read_int();
        if (t == 0) {
            d.merge(u, v);
        } else {
            cout << d.same(u, v) << LF;
        }
    }
}
