#include "lib/prelude.hpp"

struct BitSet {
    uint32_t data;
    explicit BitSet(uint32_t data): data(data) {}
    inline bool operator[](int i) const noexcept { return (data >> i) & 1; }
    inline int size() const noexcept { return __builtin_popcount(data); }
};
template<class Func>
void foreach_subset(int n, Func f) {
    for (uint32_t S = 0; S < (uint32_t)(1 << n); ++S) {
        f(BitSet(S));
    }
}

int main() {
    int N = read_int();
    int M = read_int();
    int X = read_int();
    vector C(N, int());
    vector A(N, vector(M, int()));
    REP(i, N) {
        C[i] = read_int();
        REP(k, M) { A[i][k] = read_int(); }
    }

    int ans = numeric_limits<int>::max();
    foreach_subset(N, [&](BitSet S) {
        vector<int> xs(M);
        REP(i, N) if (S[i]) {
            REP(k, M) { xs[k] += A[i][k]; }
        }
        if (all_of(ALL(xs), [X](int x) { return x >= X; })) {
            int price = 0;
            REP(i, N) if (S[i]) { price += C[i]; }
            assign_min(ans, price);
        }
    });

    if (ans == numeric_limits<int>::max()) {
        cout << -1 << LF;
    } else {
        cout << ans << LF;
    }
}
