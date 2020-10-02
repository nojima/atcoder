#include "lib/prelude.hpp"
#include "lib/segment_tree.hpp"

int main() {
    auto N = read_int();
    auto K = read_int();
    vector<int64_t> A(N);
    REP(i, N) { A[i] = read_int(); }

    int64_t Amax = numeric_limits<int64_t>::min();
    REP(i, N) { assign_max(Amax, A[i]); }

    // dp[i]: i番目までの条件を満たす最大の長さ
    vector dp(N, int64_t());
    SegmentTree st(Amax+1,
        int64_t(0),
        [](auto x, auto y){ return max(x, y); });
    REP(i, N) {
        dp[i] = 1;
        if (i > 0) { assign_max(dp[i], dp[i-1]); }
        // A[j] が A[i]-K .. A[i]+K の範囲に入っているような j に対する dp[j] の最大値
        int64_t v = st.prod(max<int64_t>(0, A[i]-K), min(Amax+1, A[i]+K+1)) + 1;
        assign_max(dp[i], v);

        if (st.get(A[i]) < v) {
            st.set(A[i], v);
        }
    }
    cout << dp[N-1] << LF;
}
