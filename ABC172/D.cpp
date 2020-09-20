#include "../lib/prelude.hpp"

int main() {
    auto N = read_int();

    int64_t ans = 0;
    for (int k = 1; k <= N; ++k) {
        // k <= xk <= N
        // ∴ 1 <= x <= N/k
        //
        // m = N/k とする
        //   k + 2k + ... + mk
        // = k (1 + ... + m)
        // = k m (m+1) / 2
        auto m = N/k;
        ans += k * m * (m+1) / 2;
    }
    cout << ans << LF;
}
