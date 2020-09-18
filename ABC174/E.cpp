#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

// 区間[a, b)の中で最初に pred(x) = true となるような x を返す
template <class Pred>
int64_t bin_search(int64_t a, int64_t b, Pred pred) {
    if (a + 1 == b) return b;
    int64_t m = a + (b - a) / 2;
    if (pred(m))
        return bin_search(a, m, pred);
    else
        return bin_search(m, b, pred);
}

inline int64_t div_ceil(int64_t a, int64_t b) noexcept {
    return (a + b - 1) / b;
}

int main() {
    int N; cin >> N;
    int64_t K; cin >> K;
    vector<int64_t> A(N);
    REP(i, N) cin >> A[i];

    int64_t S = 0;
    REP(i, N) S += A[i];

    int64_t ans = bin_search(0, S+1, [&](int64_t L) {
        // 最大の丸太の長さが L 以下になるように切ることができるか
        int64_t k = 0;
        REP(i, N) k += div_ceil(A[i], L) - 1;
        return k <= K;
    });
    cout << ans << '\n';
}
