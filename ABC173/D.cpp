#include "lib/prelude.hpp"

int main() {
    int N = read_int();
    vector<int64_t> A(N);
    REP(i, N) A[i] = read_int();

    sort(ALL(A), greater());

    int64_t score = A[0];
    int k = 1;
    for (int i = 2; i < N; ++i) {
        score += A[k];
        if (i % 2 == 1) ++k;
    }
    cout << score << LF;
}
