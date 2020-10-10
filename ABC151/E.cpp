#include "lib/prelude.hpp"
#include "lib/modint.hpp"

template<class Int>
struct Combination {
    Int fact(int n) {
        if (n < (int)facts.size()) { return facts[n]; }
        for (int i = facts.size(); i <= n; ++i) {
            facts.emplace_back(facts[i-1] * i);
        }
        return facts[n];
    }
    Int inv_fact(int n) {
        if (n < (int)inv_facts.size()) { return inv_facts[n]; }
        fact(n); // fill facts[0..n]
        for (int i = inv_facts.size(); i <= n; ++i) {
            inv_facts.emplace_back(facts[i].inverse());
        }
        return inv_facts[n];
    }
    Int nCr(int n, int r) {
        if (n < r) { return Int(0); }
        return fact(n) * inv_fact(r) * inv_fact(n-r);
    }
private:
    vector<Int> facts = {1};
    vector<Int> inv_facts;
};


using mint = ModInt<int(1e9+7)>;

int main() {
    auto N = read_int();
    auto K = read_int();
    vector<int> A(N);
    REP(i, N) { A[i] = read_int(); }
    sort(ALL(A));

    Combination<mint> cmb;

    mint s_max, s_min;
    REP(i, N) { s_max += mint(A[i]) * cmb.nCr(i, K-1); }
    REP(i, N) { s_min += mint(A[i]) * cmb.nCr(N-i-1, K-1); }
    cout << s_max - s_min << LF;
}
