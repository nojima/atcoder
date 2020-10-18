#include "lib/prelude.hpp"
#include "lib/binary_search.hpp"
#include "lib/cumsum.hpp"

template<class T, class Func>
void foreach_permutation(vector<T>& seq, const Func& f, int i = 0) {
    if(i == (int)seq.size()) {
        f();
        return;
    }
    for(int j = 0; j < (int)seq.size(); ++j) {
        swap(seq[i], seq[j]);
        foreach_permutation(seq, f, i+1);
        swap(seq[i], seq[j]);
    }
}

int main() {
    auto N = read_int();
    auto M = read_int();
    vector<int64_t> w(N), l(M), v(M);
    REP(i, N) { w[i] = read_int(); }
    REP(i, M) {
        l[i] = read_int();
        v[i] = read_int();
    }

    // 必ず橋が崩落するか調べる
    REP(i, N) REP(j, M) {
        if(w[i] > v[j]) {
            cout << -1 << LF;
            return 0;
        }
    }

    foreach_permutation(w, [&]{
        // i番目のラクダの位置を x[i] とする (x[0] = 0)
        // i番目のラクダに関する制約:
        //   w[i] <= min_{j}{ v[j] }
        //   w[i]+w[i-1] <= min_{l[j] <= x[i]-x[i-1]}{ v[j] }
        //   w[i]+w[i-1]+w[i-2] <= min_{l[j] <= x[i]-x[i-2]}{ v[j] }
        // i番目とi-1番目の間隔をs[i]とすると:
        //   w[i] <= min_{j}{ v[j] }
        //   w[i]+w[i-1] <= min_{l[j] <= s[i]}{ v[j] }
        //   w[i]+w[i-1]+w[i-2] <= min_{l[j] <= s[i]+s[i-1]}{ v[j] }
    });
}
