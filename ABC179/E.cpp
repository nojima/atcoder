#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/operators.hpp>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

// a を m で割った余り(>=0)を返す。
constexpr inline int mod(int a, int m) noexcept {
    int r = a % m;
    return r < 0 ? r + m : r;
}

int main() {
    int64_t N, X, M; cin >> N >> X >> M;

    // X + X^2 + X^4 + X^8 + ... (mod M)
    vector<int64_t> seen(M+1, -1);
    vector<int64_t> sum(M+10);

    int64_t a = X;
    int64_t S = 0;
    for (int64_t i = 1; i <= N; ++i) {
        S += a;
        if (i < (int)sum.size()) sum[i] = sum[i-1] + a;

        if (i < (int)sum.size() && seen[a] != -1) {
            int64_t period = i - seen[a];
            int64_t loop_sum = sum[i] - sum[seen[a]];
            int64_t n_loop = (N-i) / period;
            S += n_loop * loop_sum;
            i += n_loop * period;
        }
        seen[a] = i;

        a = (a * a) % M;
    }
    cout << S << endl;
}
