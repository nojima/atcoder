#include "lib/prelude.hpp"

int main() {
    int N = read_int();
    vector<int64_t> A(N);
    REP(i, N) A[i] = read_int();

    // i < j とすると
    //   j - i = A[j] + A[i]
    //   ∴ j - A[j] = A[i] + i

    map<int64_t, int64_t> B;
    REP(i, N) B[A[i] + i] += 1;

    int64_t ans = 0;
    REP(j, N) ans += B[j - A[j]];
    cout << ans << LF;
}
