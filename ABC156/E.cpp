#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include "lib/combination.hpp"

using mint = ModInt<int(1e9+7)>;

// 部屋n個にk人を入れる場合の数
mint f(Combination<mint>& cmb, int n, int k) {
    return cmb.fact(k+n-1) * cmb.inv_fact(k) * cmb.inv_fact(n-1);
}

int main() {
    auto n = read_int();
    auto k = read_int();
    Combination<mint> cmb;

    if(k >= n-1) {
        cout << f(cmb, n, n) << LF;
    } else {
        mint ans;
        REP(z, k+1) {
            ans += f(cmb, n-z, z) * cmb.nCr(n, z);
        }
        cout << ans << LF;
    }
}
