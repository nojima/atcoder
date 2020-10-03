#include "lib/prelude.hpp"
#include "lib/bit_set.hpp"
#include "lib/modint.hpp"
#include "lib/combination.hpp"
#include "lib/debug.hpp"

using mint = ModInt<1000000007>;

int main() {
    Combination<mint> cmb;

    int N = read_int();
    vector<int> A(N);
    REP(i, N) A[i] = read_int();

    mint e;
    vector<mint> C(N+1);
    for (int k = N; k >= 1; --k) {
        // 長さが k の最長増加部分列がいくつあるか数える

        mint cnt;
        foreach_power_set(N, [&](BitSet S){
            if (S.size() != k) { return; }

            // Sが増加列になっている場合の数を数える
            vector<int> B;
            REP(i, N) if(S[i]) { B.push_back(A[i]); }

            for (int i = (int)B.size()-2; i >= 0; --i) {
                if (B[i] >= B[i+1]) {
                    B[i] = B[i+1]-1;
                }
            }
            cout << B << endl;

            mint c;
            int nb = B.size();
            for(int i = nb-1, i >= 0; --i)) {
                mint m1 = cmb.nCr(B[i], nb-i+1);
                if (i >= 1) {
                    mint m2 = cmb.nCr(B[i]-B[i-1], nb-i+1);
                    mint m3 = cmb.nCr(B[i-1], nb-i);
                    c += m1 - m2 - m3;
                    cout << m1 << " " << m2 << " " << m3 << endl;
                } else {
                    c += m1;
                }
                cout << c << endl;
            }
            cnt += c;
        });
        C[k] = cnt;

        // 包除原理により、長さ k の最長部分増加列の数は
        // C_k - C_{k+1} + C_{k+2} ...
        mint acc = cnt;
        int sgn = -1;
        for (int i = k+1; i <= N; ++i) {
            acc += mint(sgn) * C[i];
            sgn *= -1;
        }
        cout << k << " " << acc << endl;

        e += acc * k;
    }
    cout << C << endl;

    mint all(1);
    REP(i, N) { all *= A[i]; }
    e /= all;

    cout << e << endl;
}
