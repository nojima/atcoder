#include "lib/prelude.hpp"

int main() {
    auto N = read_int();
    auto K = read_int();
    vector<int64_t> A(N);
    REP(i, N) A[i] = read_int();

    // dp[i][k]: 
    vector dp(N, vector(K+1, bool()));
}
