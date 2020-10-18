#include "lib/prelude.hpp"

int main() {
    auto N = read_int();
    vector<int64_t> A(N);
    REP(i, N) { A[i] = read_int(); }

    set<int64_t> hand;
    REP(i, N) { hand.insert(A[i]); }
    while(hand.size() > 1) {
        auto x = *hand.begin();
        auto X = *hand.rbegin();
        hand.erase(X);
        hand.insert(X-x);
    }
    cout << *hand.begin() << LF;
}
