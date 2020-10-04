#include "lib/prelude.hpp"
#include "lib/modint.hpp"

using mint = ModInt<int(1e9+7)>;

mint nCr(int64_t n, int64_t r) {
    mint ret(1);
    REP(i, r) ret *= n-i;
    REP(i, r) ret /= i+1;
    return ret;
}

int main() {
    auto n = read_int();
    auto a = read_int();
    auto b = read_int();
    cout << mint(2).pow(n) - nCr(n, a) - nCr(n, b) - 1 << LF;
}
