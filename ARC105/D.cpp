#include "lib/prelude.hpp"

int main() {
    auto T = read_int();
    while(T--) {
        auto N = read_int();
        vector<int64_t> A(N);
        REP(i, N) { A[i] = read_int(); }

        int64_t x = 0;
        REP(i, N) { x ^= A[i]; }
        bool a = (x == 0);
        bool b = (N % 2 == 0);
        bool c = a ^ b;
        cout << (c ? "First" : "Second") << LF;
    }
}
