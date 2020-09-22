#include "lib/prelude.hpp"
#include "lib/cumsum.hpp"
#include "lib/binary_search.hpp"

int main() {
    int N = read_int();
    int M = read_int();
    int64_t K = read_int();
    vector<int64_t> A(N), B(M);
    REP(i, N) A[i] = read_int();
    REP(i, M) B[i] = read_int();

    auto cumsum_a = make_cumsum(A);
    auto cumsum_b = make_cumsum(B);

    int64_t ans = 0;
    REP(a, N+1) {
        // 机Aの本を a 冊読むとする
        auto time_a = sum_of(cumsum_a, 0, a);
        if (time_a > K) break;
        auto max_b = bin_search(1, M+1, [&](int b) {
            auto time_b = sum_of(cumsum_b, 0, b);
            return (time_a + time_b) > K;
        });
        assign_max(ans, a + max_b - 1);
    }
    cout << ans << LF;
}
