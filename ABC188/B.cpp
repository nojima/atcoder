#include "lib/prelude.hpp"

int main() {
    auto N = read_int();
    vector<int64_t> A(N), B(N);
    REP(i, N) A[i] = read_int();
    REP(i, N) B[i] = read_int();

    int64_t dot = 0;
    REP(i, N) dot += A[i] * B[i];

    cout << (dot == 0 ? "Yes" : "No") << endl;
}
