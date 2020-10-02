#include "lib/prelude.hpp"
#include "lib/fix.hpp"

struct Query {
    int a, b, c, d;
};

int main() {
    int N = read_int();
    int M = read_int();
    int Q = read_int();
    vector<Query> queries(Q);
    REP(i, Q) {
        int a = read_int() - 1;
        int b = read_int() - 1;
        int c = read_int();
        int d = read_int();
        queries[i] = {a, b, c, d};
    }

    vector<int> A(N);
    auto brute_force = Fix([&](auto&& self, int i, int min_k) -> int {
        if (i == N) {
            int score = 0;
            REP(i, Q) {
                auto [a, b, c, d] = queries[i];
                if (A[b] - A[a] == c) { score += d; }
            }
            return score;
        } else {
            int max_score = 0;
            FOR(k, min_k, M+1) {
                A[i] = k;
                assign_max(max_score, self(i+1, k));
            }
            return max_score;
        }
    });
    cout << brute_force(0, 1) << LF;
}
