#include "lib/prelude.hpp"

int main() {
    int N = read_int();
    vector<int> A(1 << N);
    vector<int> I(1 << N);
    REP(i, 1 << N) A[i] = read_int();
    REP(i, 1 << N) I[i] = i + 1;

    REP(round, N-1) {
        int n = 1 << (N - round);
        int k = 0;
        for (int j = 0; j < n; j += 2, ++k) {
            if (A[j] < A[j+1]) {
                A[k] = A[j+1];
                I[k] = I[j+1];
            } else {
                A[k] = A[j];
                I[k] = I[j];
            }
        }
    }
    if (A[0] < A[1]) {
        cout << I[0] << endl;
    } else {
        cout << I[1] << endl;
    }
}
