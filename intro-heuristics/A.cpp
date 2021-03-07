#include "lib/prelude.hpp"
#include "lib/xoshiro256.hpp"
#include "lib/debug.hpp"
#include <chrono>

using Contest = int;

int n_days;
vector<int64_t> C;
vector<vector<int64_t>> S;

Xoshiro256 rng;

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

int64_t calculate_score(const vector<Contest>& schedule) {
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

vector<Contest> make_initial_solution() {
    vector<Contest> schedule(n_days);
    REP(d, n_days) {
        schedule[d] = rng() % 26;
    }
    return schedule;
}

void print_solution(const vector<Contest>& schedule) {
    REP(d, n_days) {
        cout << schedule[d]+1 << LF;
    }
}

class Stopwatch {
    chrono::steady_clock::time_point t0;

public:
    Stopwatch(): t0(chrono::steady_clock::now()) {}
    int64_t elapsed_millis() {
        auto now = chrono::steady_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now - t0).count();
    }
};

int main() {
    Stopwatch stopwatch;

    ios::sync_with_stdio(false);

    read_input();

    auto schedule = make_initial_solution();
    auto current_score = calculate_score(schedule);

    for(int iteration = 0; ; ++iteration) {
        if(iteration % 1000 == 0) {
            if(stopwatch.elapsed_millis() > 1800) {
                DEBUG(cerr << "iteration = " << iteration << endl);
                break;
            }
        }

        auto d = rng() % n_days;
        auto q = rng() % 26;
        auto old = schedule[d];
        schedule[d] = q;
        auto new_score = calculate_score(schedule);
        if(new_score > current_score) {
            current_score = new_score;
        } else {
            schedule[d] = old;
        }
    }

    print_solution(schedule);
    DEBUG(cerr << "score = " << calculate_score(schedule) << endl);
}
