#include "lib/prelude.hpp"

using Day = int;
using Contest = int;

int n_days;
vector<int64_t> C;
vector<vector<int64_t>> S;

void read_input() {
    n_days = read_int();

    C.resize(26);
    REP(i, 26) {
        C[i] = read_int();
    }

    S.resize(n_days, vector(26, int64_t(0)));
    REP(i, n_days) REP(j, 26) {
        S[i][j] = read_int();
    }
}

int64_t calculate_score(const vector<int>& schedule) {
    int64_t satisfaction = 0;
    vector<int> last(26, -1);

    for(int d = 0; d < n_days; ++d) {
        int t_held = schedule[d];
        satisfaction += S[d][t_held];
        last[t_held] = d;
        for(int t = 0; t < 26; ++t) {
            satisfaction -= C[t] * (d - last[t]);
        }
    }

    return satisfaction;
}

int main() {
    read_input();

    // read current solution
    vector<Contest> schedule(n_days);
    REP(d, n_days) schedule[d] = read_int()-1;

    // process query
    int M = read_int();
    REP(m, M) {
        int d = read_int()-1;
        int q = read_int()-1;
        schedule[d] = q;
        cout << calculate_score(schedule) << '\n';
    }
}
