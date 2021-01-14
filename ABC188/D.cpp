#include "lib/prelude.hpp"

enum EventType { BEGIN, END };

struct Event {
    EventType type;
    int64_t t;
    int64_t cost;
};

int main() {
    int N = read_int();
    auto C = read_int();
    vector<int64_t> a(N), b(N), c(N);
    REP(i, N) {
        a[i] = read_int();
        b[i] = read_int();
        c[i] = read_int();
    }

    vector<Event> events;
    REP(i, N) {
        events.push_back({ BEGIN, a[i],  c[i] });
        events.push_back({ END, b[i]+1, -c[i] });
    }

    sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
        if (e1.t != e2.t) return e1.t < e2.t;
        return e1.type > e2.type;
    });

    int64_t current_sum = 0, paid_day = 0, paid = 0;
    for (const auto& e : events) {
        if (e.t > paid_day) {
            paid += min(current_sum, C) * (e.t - paid_day);
            paid_day = e.t;
        }
        current_sum += e.cost;
    }

    cout << paid << endl;
}
