#include "lib/prelude.hpp"
#include "lib/xoshiro256.hpp"
#include "lib/stopwatch.hpp"
#include "lib/debug.hpp"

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

inline double lerp(double x, double y, double alpha) {
    return x + (y - x) * alpha;
}

vector<Contest> simulated_annealing(const Stopwatch& stopwatch, int64_t time_limit_millis) {
    auto schedule = make_initial_solution();
    auto current_score = calculate_score(schedule);
    vector<Contest> best_schedule;
    int64_t best_score = numeric_limits<int64_t>::min();

    const double initial_temperature = 1500.0;
    const double final_temperature = 100.0;
    double temperature = initial_temperature;
    double start_time = stopwatch.elapsed_millis();

    for(int iteration = 0; ; ++iteration) {
        if(iteration % 1000 == 0) {
            auto elapsed = stopwatch.elapsed_millis();
            if(elapsed >= time_limit_millis) {
                //DEBUG(cerr << "iteration = " << iteration << endl);
                return best_schedule;
            }

            // 温度を調整
            double progress = (double)(elapsed - start_time) / (time_limit_millis - start_time);
            temperature = lerp(initial_temperature, final_temperature, progress);
        }

        // 近傍を選ぶ
        auto d = rng() % n_days;
        auto q = rng() % 26;
        auto old = schedule[d];
        schedule[d] = q;
        auto new_score = calculate_score(schedule);

        // 遷移するか決める
        bool ok;
        if(new_score >= current_score) {
            ok = true;
        } else {
            int64_t delta = current_score - new_score;
            double accept_prob = exp(-delta / temperature);
            ok = rng.next_double() < accept_prob;
        }

        if(ok) { // 遷移する
            current_score = new_score;
            if(current_score > best_score) {
                best_score = current_score;
                best_schedule = schedule;
            }
        } else { // 遷移しない
            schedule[d] = old;
        }
    }
}

void print_solution(const vector<Contest>& schedule) {
    REP(d, n_days) {
        cout << schedule[d]+1 << LF;
    }
}

int main() {
    Stopwatch stopwatch;
    ios::sync_with_stdio(false);
    read_input();
    auto schedule = simulated_annealing(stopwatch, 1800);
    print_solution(schedule);
    DEBUG(cerr << "score = " << calculate_score(schedule) << endl);
}
