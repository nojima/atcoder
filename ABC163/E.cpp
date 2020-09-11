#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

template <class T, class Compare>
vector<int> sort_index(const vector<T>& v, Compare comp) {
    vector<int> index(v.size());
    REP(i, v.size()) index[i] = i;
    sort(ALL(index), [&](int i, int j) { return comp(v[i], v[j]); });
    return index;
}

int main() {
    int N; cin >> N;
    vector<int64_t> A(N);
    REP(i, N) cin >> A[i];

    auto index = sort_index(A, greater());

    // dp[L][R] = 左にL人、右にR人配置したときの嬉しさの最大値
    vector dp(N+1, vector(N+1, int64_t()));
    REP(L, N+1) REP(R, N-L+1) {
        if (L == 0 && R == 0) {
            dp[L][R] = 0;
        } else {
            auto k = index[L+R-1];
            int64_t vl = L >= 1 ? dp[L-1][R] + A[k] * abs(k+1 - L)
                                : numeric_limits<int64_t>::min();
            int64_t vr = R >= 1 ? dp[L][R-1] + A[k] * abs(k+1 - (N-R+1))
                                : numeric_limits<int64_t>::min();
            dp[L][R] = max(vl, vr);
        }
    }

    int64_t ans = numeric_limits<int64_t>::min();
    REP(L, N+1) ans = max(ans, dp[L][N-L]);
    cout << ans << '\n';
}
