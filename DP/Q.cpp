#include "lib/prelude.hpp"
#include "lib/segment_tree.hpp"

int main() {
    int N = read_int();
    vector<int64_t> H(N), A(N);
    REP(i, N) { H[i] = read_int(); }
    REP(i, N) { A[i] = read_int(); }

    // dp(i, h):
    //   i番目までの花だけを考える。
    //   問題の条件を満たし、かつ高さの最大値が h になるようにする。
    //   このときの美しさの総和の最大値。
    //   (i についてインライン化して計算する)
    SegmentTree dp(
        N+1,
        int64_t(0), // identity
        [](int64_t a, int64_t b) { return max(a, b); } // product
    );

    REP(i, N) {
        dp.set(H[i], dp.prod(1, H[i]) + A[i]);
    }

    cout << dp.prod(1, N+1) << LF;
}
