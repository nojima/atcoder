#include "lib/prelude.hpp"

int main() {
    vector<int64_t> A(4);
    REP(i, 4) { A[i] = read_int(); }
    int all_sum = A[0]+A[1]+A[2]+A[3];

    bool ok = false;
    REP(a, 2) REP(b, 2) REP(c, 2) REP(d, 2) {
        if (a+b+c+d > 0) {
            int64_t sum = 0;
            if(a > 0) sum += A[0];
            if(b > 0) sum += A[1];
            if(c > 0) sum += A[2];
            if(d > 0) sum += A[3];
            if(sum == all_sum-sum) {
                ok = true;
            }
        }
    }
    if (ok) cout << "Yes\n";
    else cout << "No\n";
}
