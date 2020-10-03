#include "lib/prelude.hpp"
#include "lib/io/string.hpp"
#include "lib/modint.hpp"
#include "lib/combination.hpp"

using mint = ModInt<int(1e9+7)>;

int main() {
    Combination<mint> cmb;
    auto K = read_int();
    string S = read_word();

    int l = S.length();
    mint ans;
    REP(k, K+1) {
        mint a = cmb.fact(k+l-1);
        mint b = cmb.inv_fact(k) * cmb.inv_fact(l-1);
        mint c = mint(25).pow(k);
        mint d = mint(26).pow(K-k);
        //cout << vector{a * b, c, d, a * b * c * d} << LF;
        ans += a * b * c * d;
    }
    cout << ans << LF;
}
