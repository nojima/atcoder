#include "lib/prelude.hpp"
#include "lib/xoshiro256.hpp"
#include "lib/stopwatch.hpp"

using Contest = int;

int n_days;
vector<int64_t> C;
vector<vector<int64_t>> S;

Xoshiro256 rng;

template <class Func1, class Func2, class Func3>
void simulated_annealing(
    int64_t time_limit_millis,
    int64_t initial_score,
    Func1 move_to_neighbor,
    Func2 undo_move,
    Func3 on_best_score_updated
) {
    Stopwatch stopwatch;

    const double initial_temperature = 10000.0;
    double temperature = initial_temperature;

    int64_t current_score = initial_score;
    int64_t best_score = initial_score;

    for(int iteration = 0; ; ++iteration) {
        if(iteration % 100 == 0) {
            auto elapsed = stopwatch.elapsed_millis();
            if(elapsed >= time_limit_millis) {
                return;
            }

            // 温度を調整
            double progress = (double)elapsed / time_limit_millis;
            temperature = initial_temperature * (1.0 - progress) * exp2(-progress);
        }

        // 近傍からランダムに遷移先を選ぶ
        auto [new_score, undo_info] = move_to_neighbor(current_score);

        // 遷移を採用するか決める
        bool ok;
        if(new_score >= current_score) {
            ok = true;
        } else {
            int64_t delta = current_score - new_score;
            double accept_prob = exp(-delta / temperature);
            ok = rng.next_double() < accept_prob;
        }

        if(ok) { // 採用する
            current_score = new_score;
            if(current_score > best_score) {
                best_score = current_score;
                on_best_score_updated();
            }
        } else { // 採用しない
            undo_move(undo_info);
        }
    }
}

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

inline int64_t calculate_penalty(int k) {
    return k * (k+1) / 2;
}

int64_t calculate_score_delta_on_contest_remove(
    vector<set<int>>& contest_date_list, int day, Contest contest
) {
    auto& l = contest_date_list[contest];
    auto it = l.find(day);
    int prev_day = *prev(it);
    int next_day = *next(it);

    int d1 = next_day - prev_day - 1; // コンテストが開催されなかった日数
    int d2 = day - prev_day - 1;
    int d3 = next_day - day - 1;

    int64_t p1 = calculate_penalty(d1);
    int64_t p2 = calculate_penalty(d2);
    int64_t p3 = calculate_penalty(d3);

    l.erase(day);

    auto delta = p2 + p3 - p1;
    return delta * C[contest] - S[day][contest];
}

int64_t calculate_score_delta_on_contest_add(
    vector<set<int>>& contest_date_list, int day, Contest contest
) {
    auto& l = contest_date_list[contest];
    auto it = l.lower_bound(day);
    int next_day = *it;
    int prev_day = *prev(it);

    int d1 = next_day - prev_day - 1; // コンテストが開催されなかった日数
    int d2 = day - prev_day - 1;
    int d3 = next_day - day - 1;

    int64_t p1 = calculate_penalty(d1);
    int64_t p2 = calculate_penalty(d2);
    int64_t p3 = calculate_penalty(d3);

    l.insert(day);

    auto delta = p1 - p2 - p3;
    return delta * C[contest] + S[day][contest];
}

vector<Contest> solve(int64_t time_limit_millis) {
    auto schedule = make_initial_solution();
    auto best_schedule = schedule;

    // contest_date_list を初期化
    vector<set<int>> contest_date_list(26);
    for(auto& l : contest_date_list) {
        l.insert(-1);
        l.insert(n_days);
    }
    for(int d = 0; d < n_days; ++d) {
        Contest contest = schedule[d];
        contest_date_list[contest].insert(d);
    }

    enum Action { kSwap, kReplace };
    struct UndoInfo {
        Action action;
        Contest old;
        int day;
        int offset;
    };

    simulated_annealing(
        time_limit_millis, calculate_score(schedule),

        [&](int64_t current_score) { // move_to_neighbor
            if(rng.next_double() < 0.25) {
                // 選んだ日のコンテストをランダムに置き換える
                int day = rng() % n_days;
                Contest old = schedule[day];
                Contest next;
                do {
                    next = rng() % 26;
                } while(next == old);
                schedule[day] = next;
                int64_t new_score = current_score +
                    calculate_score_delta_on_contest_remove(contest_date_list, day, old) +
                    calculate_score_delta_on_contest_add(contest_date_list, day, next);

                return pair<int64_t, UndoInfo>(
                    new_score,
                    { kReplace, old, day, 0 }
                );
            } else {
                // 選んだ日のコンテストを近くの日と入れ替える
                int offset = rng() % 8 + 1;
                if(n_days - offset <= 0) { offset = 1; }
                int day = rng() % (n_days - offset);
                int64_t new_score = current_score +
                    calculate_score_delta_on_contest_remove(contest_date_list, day, schedule[day]) +
                    calculate_score_delta_on_contest_remove(contest_date_list, day+offset, schedule[day+offset]) +
                    calculate_score_delta_on_contest_add(contest_date_list, day, schedule[day+offset]) +
                    calculate_score_delta_on_contest_add(contest_date_list, day+offset, schedule[day]);
                swap(schedule[day], schedule[day+offset]);

                return pair<int64_t, UndoInfo>(
                    new_score,
                    { kSwap, 0, day, offset }
                );
            }
        },

        [&](const UndoInfo& info) { // undo_move
            auto day = info.day;
            auto old = info.old;
            auto offset = info.offset;
            // 状態を元に戻す
            if(info.action == kReplace) {
                Contest curr = schedule[day];
                contest_date_list[curr].erase(day);
                contest_date_list[old].insert(day);
                schedule[day] = old;
            } else {
                contest_date_list[schedule[day]].erase(day);
                contest_date_list[schedule[day+offset]].erase(day+offset);
                contest_date_list[schedule[day]].insert(day+offset);
                contest_date_list[schedule[day+offset]].insert(day);
                swap(schedule[day], schedule[day+offset]);
            }
        },

        [&]() { // on_best_score_updated
            best_schedule = schedule;
        }
    );

    return best_schedule;
}

void print_solution(const vector<Contest>& schedule) {
    REP(d, n_days) {
        cout << schedule[d]+1 << LF;
    }
}

int main() {
    ios::sync_with_stdio(false);
    read_input();
    auto schedule = solve(1800);
    print_solution(schedule);

#ifndef ONLINE_JUDGE
    cerr << "score = " << calculate_score(schedule) << endl;
#endif
}
