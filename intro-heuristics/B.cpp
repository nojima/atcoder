#include "lib/prelude.hpp"

vector<int64_t> calculate_score(
    int n_days,
    const vector<int>& C,
    const vector<vector<int64_t>>& S,
    const vector<int>& schedule
) {
    int64_t satisfaction = 0;
    vector<int> last(26, -1);
    vector<int64_t> scores;
    for(int d = 0; d < n_days; ++d) {
        int t_held = schedule[d];
        satisfaction += S[d][t_held];
        last[t_held] = d;
        for(int t = 0; t < 26; ++t) {
            satisfaction -= C[t] * (d - last[t]);
        }
        scores.push_back(satisfaction);
    }

    return scores;
}

int main() {
    int n_days = read_int();

    vector<int> C(26);
    REP(i, 26) {
        C[i] = read_int();
    }

    vector S(n_days, vector(26, int64_t(0)));
    REP(i, n_days) REP(j, 26) {
        S[i][j] = read_int();
    }

    vector<int> schedule(n_days);
    REP(i, n_days) {
        schedule[i] = read_int() - 1;
    }

    auto scores = calculate_score(n_days, C, S, schedule);
    for(int64_t s : scores) {
        cout << s << "\n";
    }
}
