#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

static const int64_t INF = 1e15;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

struct Route {
    int src_city;
    int dst_city;
    int fare;
    int time;
};

struct Change {
    int rate;
    int time;
};

struct Vertex {
    int city;
    int coin;
};

struct Edge {
    Vertex src;
    Vertex dst;
    int64_t weight;
};

struct Graph {
    int total_fare;
    vector<vector<Edge>> g;

    Graph(int n_cities, int total_fare)
        : total_fare(total_fare), g(n_cities * (total_fare + 1))
    {
    }

    size_t size() const {
        return g.size();
    }

    size_t index(Vertex v) const {
        return v.city * (total_fare + 1) + v.coin;
    }

    vector<Edge>& operator[](Vertex v) {
        return g[index(v)];
    }

    const vector<Edge>& operator[](Vertex v) const {
        return g[index(v)];
    }
};


template <typename Graph, typename Vertex>
vector<int64_t> dijkstra(const Graph& g, Vertex source) {
    struct State {
        Vertex vertex;
        int64_t weight;
        bool operator<(const State& other) const {
            return weight > other.weight;
        }
    };

    vector<int64_t> dists(g.size(), INF);
    vector<bool> visited(g.size());

    priority_queue<State> Q;
    Q.push({ source, 0 });
    dists[g.index(source)] = 0;

    while (!Q.empty()) {
        State s = Q.top(); Q.pop();
        int src = g.index(s.vertex);

        if (visited[src]) continue;
        visited[src] = true;

        for (const auto& e : g[s.vertex]) {
            int dst = g.index(e.dst);
            int64_t new_dist = dists[src] + e.weight;
            if (new_dist >= dists[dst]) continue;
            dists[dst] = new_dist;
            Q.push({e.dst, new_dist});
        }
    }

    return dists;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, S; cin >> N >> M >> S;

    vector<Route> routes(M);
    REP(i, M) {
        int U, V, A, B; cin >> U >> V >> A >> B;
        U--; V--;
        routes[i] = {U, V, A, B};
    }

    vector<Change> changes(N);
    REP(i, N) {
        int C, D; cin >> C >> D;
        changes[i] = {C, D};
    }

    int total_fare = 0;
    REP(i, M) total_fare += routes[i].fare;

    Graph g(N, total_fare);
    for (const auto& r : routes) {
        FOR(s, r.fare, total_fare + 1) {
            g[{r.src_city, s}].push_back({{r.src_city, s}, {r.dst_city, s - r.fare}, r.time});
            g[{r.dst_city, s}].push_back({{r.dst_city, s}, {r.src_city, s - r.fare}, r.time});
        }
    }
    REP(v, N) {
        const auto& c = changes[v];
        FOR(s, 0, total_fare) {
            g[{v, s}].push_back({{v, s}, {v, min(s + c.rate, total_fare)}, c.time});
        }
    }

    S = min(S, total_fare);
    vector<int64_t> dists = dijkstra(g, (Vertex){0, S});

    FOR(v, 1, N) {
        int64_t min_time = INF;
        REP(s, total_fare+1) {
            min_time = min(min_time, dists[g.index({v, s})]);
        }
        cout << min_time << "\n";
    }
}
