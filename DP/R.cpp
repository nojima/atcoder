#include "lib/prelude.hpp"
#include "lib/modint.hpp"
#include "lib/matrix.hpp"

using mint = ModInt<int(1e9+7)>;
using matrix = Matrix<mint>;

int main() {
    int N = read_int();
    int64_t K = read_int();
    vector adj(N, vector(N, mint(0)));
    REP(v, N) REP(w, N) {
        adj[v][w] = mint(read_int());
    }

    auto adj_k = matrix_pow(adj, K);

    vector d_0(N, mint(1));
    auto d_k = matrix_vector_mul(adj_k, d_0);

    auto ans = accumulate(ALL(d_k), mint(0));
    cout << ans << LF;
}
