#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include <boost/rational.hpp>

using mint = ModInt<1000000007>;
using Ratio = boost::rational<int64_t>;

int main() {
    int N = read_int();
    vector<int64_t> A(N), B(N);
    REP(i, N) {
        A[i] = read_int();
        B[i] = read_int();
    }

    mint n_zero(0);

    // A[i]A[j] + B[i]B[j] == 0
    // <=> A[i]/B[i] == -B[j]/A[j]

    // key: A[i]/B[i], value: 個数
    map<Ratio, int> R;
    REP(i, N) {
        if (A[i] == 0 && B[i] == 0) {
            n_zero += mint(1);
        } else if (B[i] == 0) {
            Ratio r(numeric_limits<int64_t>::max());
            R[r] += 1;
        } else {
            Ratio r(A[i], B[i]);
            R[r] += 1;
        }
    }

    mint ans(1);
    for (auto [r, cnt] : R) {
        if (cnt == 0) continue;
        Ratio q;
        if (r == 0) {
            q = numeric_limits<int64_t>::max();
        } else {
            q = -1 / r;
        }
        if (R.count(q) == 0) {
            ans *= pow_mod(mint(2), cnt);
        } else {
            int cnt2 = R[q];
            ans *= pow_mod(mint(2), cnt) + pow_mod(mint(2), cnt2) - mint(1);
            R[q] = 0;
        }
    }
    ans += n_zero;
    ans -= mint(1);

    cout << ans << LF;
}
