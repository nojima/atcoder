#include "lib/prelude.hpp"
#include "lib/knuth_morris_pratt.hpp"

int main() {
    int N = read_int();
    vector<uint32_t> a(N), b(N);
    REP(i, N) { a[i] = read_int(); }
    REP(i, N) { b[i] = read_int(); }

    vector<uint32_t> c(2*N-1), d(N);
    REP(i, N) { c[i] = a[i] ^ a[(i+1)%N]; }
    REP(i, N) { d[i] = b[i] ^ b[(i+1)%N]; }
    REP(i, N-1) { c[i+N] = c[i]; }

    auto pma = build_pma(d);
    find_all_matches(pma, d, c, [&](int k) {
        uint32_t x = a[k] ^ b[0];
        cout << k << ' ' << x << LF;
    });
}
