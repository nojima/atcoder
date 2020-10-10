#include "lib/prelude.hpp"

// 周期tの数列{a}の最初のt項が与えられる。
// このとき
//   a[0] + a[1] + ... + a[k-1]
// を求める。
int64_t sum_of_perioidic_sequence(const vector<int64_t>& a, int64_t k) {
    int64_t t = a.size();
    if(k <= t) {
        int64_t acc = 0;
        for(int i = 0; i < k; ++i) { acc += a[i]; }
        return acc;
    } else {
        int64_t q = k / t;
        int64_t r = k % t;
        int64_t acc = 0;
        for(int i = 0; i < t; ++i) { acc += a[i]; }
        acc *= q;
        for(int i = 0; i < r; ++i) { acc += a[i]; }
        return acc;
    }
}

int main() {
    int k = read_int();
    int Q = read_int();
    vector<int64_t> d(k);
    REP(i, k) { d[i] = read_int(); }

    REP(q, Q) {
        auto n = read_int();
        auto x = read_int();
        auto m = read_int();

        vector<int64_t> dm(k);
        REP(i, k) {
            dm[i] = d[i] % m;
            if(dm[i] == 0) { dm[i] = m; }
        }
        int64_t h = (x % m) + sum_of_perioidic_sequence(dm, n-1);
        int64_t t = h / m;
        cout << (n - 1) - t << LF;
    }
}
