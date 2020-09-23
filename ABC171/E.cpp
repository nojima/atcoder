#include "lib/prelude.hpp"

int main() {
    auto N = read_int();
    vector<uint64_t> A(N);
    REP(i, N) A[i] = read_int();

    uint64_t all = 0;
    REP(i, N) all ^= A[i];

    REP(i, N) {
        if (i != 0) cout << ' ';
        cout << (A[i] ^ all);
    }
    cout << LF;
}
