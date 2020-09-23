#include "lib/prelude.hpp"

int64_t median(vector<int64_t>& X) {
    sort(ALL(X));
    int n = X.size();
    if (n % 2 == 0) {
        return X[n/2-1] + X[n/2];
    } else {
        return X[n/2];
    }
}

int main() {
    int N = read_int();
    vector<int64_t> A(N), B(N);
    REP(i, N) {
        A[i] = read_int();
        B[i] = read_int();
    }
    auto a = median(A);
    auto b = median(B);
    cout << (b - a + 1) << LF;
}
