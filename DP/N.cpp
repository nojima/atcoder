#include "lib/prelude.hpp"
#include "lib/cumsum.hpp"

int main() {
    int N = read_int();
    vector<int64_t> A(N);
    REP(i, N) A[i] = read_int();

    auto cumsum = make_cumsum(A);

    // dp(len, left):
    //   区間[left, left+len)を合体させて一匹にするときの最小コスト
    vector dp(N+1, vector(N, int64_t(0)));

    FOR(len, 2, N+1) {
        REP(left, N) {
            if (left + len > N) { break; }
            auto sum = sum_of(cumsum, left, left + len);
            int64_t min_cost = numeric_limits<int64_t>::max();
            FOR(left_len, 1, len) {
                int right_len  = len - left_len;
                int right_left = left + left_len;
                auto cost = dp[left_len][left] + dp[right_len][right_left] + sum;
                assign_min(min_cost, cost);
            }
            dp[len][left] = min_cost;
        }
    }
    cout << dp[N][0] << LF;
}
