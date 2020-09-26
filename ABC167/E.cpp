#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include "lib/combination.hpp"

using mint = ModInt<998244353>;

int main() {
    Combination<mint> cmb;

    int N = read_int();
    mint M = mint(read_int());
    int K = read_int();

    mint ans;
    REP(k, K+1) {
        // N-k 個の色を隣り合わないように塗る
        auto a = M * (M-1).pow(N-k-1);
        // 重複を許して N-k 個から k 個選ぶ
        auto b = cmb.nHr(N-k, k);
        ans += a * b;
    }
    cout << ans << LF;
}
