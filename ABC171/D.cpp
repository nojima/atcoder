#include "lib/prelude.hpp"

int main() {
    auto N = read_int();
    map<int64_t, int64_t> A; // 値 → 個数
    REP(i, N) {
        auto a = read_int();
        ++A[a];
    }

    int64_t sum = 0;
    for (auto [value, cnt] : A) {
        sum += value * cnt;
    }

    auto Q = read_int();
    REP(q, Q) {
        auto B = read_int();
        auto C = read_int();
        auto cnt = A[B];
        sum -= B * cnt;
        sum += C * cnt;
        A[C] += cnt;
        A.erase(B);
        cout << sum << LF;
    }
}
