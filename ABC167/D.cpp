#include "lib/prelude.hpp"

vector<int> make_identity_permutation(int n) {
    vector<int> ret(n);
    iota(ret.begin(), ret.end(), 0);
    return ret;
}

vector<int> concat_permutations(const vector<int>& first, const vector<int>& second) {
    assert(first.size() == second.size());
    vector<int> ret(first.size());
    for (int i = 0; i < (int)ret.size(); ++i) {
        ret[i] = second[first[i]];
    }
    return ret;
}

template<class T, class Product>
auto monoid_pow(T base, int64_t exponent, T identity, Product product) {
    T ans = move(identity);
    while (exponent > 0) {
        if (exponent & 1) {
            ans = product(ans, base);
        }
        base = product(base, base);
        exponent >>= 1;
    }
    return ans;
}

int main() {
    auto N = read_int();
    auto K = read_int();
    vector<int> A(N);
    REP(i, N) A[i] = read_int()-1;

    auto PK = monoid_pow(A, K,
        make_identity_permutation(N),
        [](const auto& p1, const auto& p2){ return concat_permutations(p1, p2); }
    );
    cout << PK[0]+1 << LF;
}
