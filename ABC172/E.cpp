#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include "lib/combination.hpp"

using mint = ModInt<int(1e9+7)>;

/*
S を {1, 2, ..., N} の部分集合とする。
各i∈Sについて A[i] = B[i] となるような場合の数は
    M個の整数から|S|個選んで並べる -> P(M, |S|)
    残りの M-|S| 個の整数から N-|S| 個選んで並べる -> P(M-|S|, N-|S|)
    ∴ P(M, |S|) * P(M-|S|, N-|S|)^2
包除原理により、A[i] = B[i] となる i が存在しないような場合の数は
    Σ_{S} (-1)^|S| * P(M, |S|) * P(M-|S|, N-|S|)^2      (*)
|S| = k となるような S の選び方は、N個から k 個選ぶ場合の数なので
    C(N, k)
よって、(*) は以下と等しい:
    Σ_{k=0}^{k=N} (-1)^k * P(M, k) * P(M-k, N-k)^2 * C(N, k)
*/

int main() {
    Combination<mint> cmb;
    auto N = read_int();
    auto M = read_int();

    mint ans;
    REP(k, N+1) {
        mint a = cmb.nPr(M, k);
        mint b = cmb.nPr(M-k, N-k);
        mint c = cmb.nCr(N, k);
        //cout << a << " " << b << " " << c << " " << a * b * b * c << LF;
        ans += mint(-1).pow(k) * a * b * b * c;
    }
    cout << ans << LF;
}
