#include "lib/prelude.hpp"
#include "lib/debug.hpp"

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

    int64_t delta = p2 + p3 - p1;
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

    int64_t delta = p1 - p2 - p3;
    return delta * C[contest] + S[day][contest];
}

int main() {
    read_input();

    // read current solution
    vector<Contest> schedule(n_days);
    REP(d, n_days) schedule[d] = read_int()-1;

    // contest_date_list を初期化
    vector<set<int>> contest_date_list(26);
    for(Contest c = 0; c < 26; ++c) {
        contest_date_list[c].insert(-1);
        contest_date_list[c].insert(n_days);
    }
    for(int d = 0; d < n_days; ++d) {
        Contest contest = schedule[d];
        contest_date_list[contest].insert(d);
    }

    // process query
    int M = read_int();
    int64_t current_score = calculate_score(schedule);
    //cerr << "init: " << current_score << '\n';
    REP(m, M) {
        int day = read_int()-1;
        int old = schedule[day];
        schedule[day] = read_int()-1;
        int64_t new_score = current_score +
                calculate_score_delta_on_contest_remove(contest_date_list, day, old) +
                calculate_score_delta_on_contest_add(contest_date_list, day, schedule[day]);
        cout << new_score << '\n';
        current_score = new_score;
    }
}
