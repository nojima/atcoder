#include "lib/prelude.hpp"
#include "lib/modint.hpp"

using mint = ModInt<1000000007>;

inline int sign(int x) {
    if(x < 0) return -1;
    if(x > 0) return 1;
    return 0;
}

int main() {
    int N = read_int();
    int K = read_int();
    vector<int> A(N);
    REP(i, N) A[i] = read_int();

    // 絶対値の大きい順に並べる
    sort(ALL(A), [](int a, int b) { return abs(a) > abs(b); });

    // 最初のK個が正ならばそれが答え
    // N == K の場合も無条件でそれが答え
    auto prod = mint(1);
    auto sgn = 1;
    REP(i, K) {
        prod *= mint(A[i]);
        sgn *= sign(A[i]);
    }
    if(sgn != -1 || N == K) {
        cout << prod << LF;
        return 0;
    }

    // 全部負の場合
    if(all_of(ALL(A), [](int a){ return a < 0; })) {
        reverse(ALL(A));
        prod = mint(1);
        REP(i, K) prod *= mint(A[i]);
        cout << prod << LF;
        return 0;
    }

    // X := 最初のK個、Y := 残ったN-K個
    // (1) Xから負の数を選ぶ、Yから非負の数を選ぶ
    // (2) Xから正の数を選ぶ、Yから負の数を選ぶ
    int x1_i = -1, y1_i = -1;
    REP(i, K) {
        if(A[i] < 0) {
            x1_i = i;
        }
    }
    REP(i, N-K) {
        if(A[i+K] >= 0) {
            y1_i = i+K;
            break;
        }
    }

    int x2_i = -1, y2_i = -1;
    REP(i, K) {
        if(A[i] > 0) {
            x2_i = i;
        }
    }
    REP(i, N-K) {
        if(A[i+K] < 0) {
            y2_i = i+K;
            break;
        }
    }

    if(x1_i >= 0 && y1_i >= 0 && x2_i >= 0 && y2_i >= 0) {
        // |y1/x1| > |y2/x2|
        // ⇔ |y1 x2| > |y2 x1|
        int64_t x1 = A[x1_i], y1 = A[y1_i], x2 = A[x2_i], y2 = A[y2_i];
        if(abs(y1 * x2) > abs(y2 * x1)) {
            swap(A[x1_i], A[y1_i]);
        } else {
            swap(A[x2_i], A[y2_i]);
        }
    } else if (x1_i >= 0 && y1_i >= 0) {
        swap(A[x1_i], A[y1_i]);
    } else if (x2_i >= 0 && y2_i >= 0) {
        swap(A[x2_i], A[y2_i]);
    }

    prod = mint(1);
    REP(i, K) prod *= mint(A[i]);
    cout << prod << LF;
}
