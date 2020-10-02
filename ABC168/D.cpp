#include "lib/prelude.hpp"

int main() {
    int N = read_int();
    int M = read_int();
    vector<vector<int>> graph(N);
    REP(i, M) {
        int a = read_int()-1;
        int b = read_int()-1;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }

    vector<int> previous(N, -1);
    queue<int> Q;
    Q.push(0);
    previous[0] = 0;
    while (!Q.empty()) {
        int v = Q.front(); Q.pop();
        for (int w : graph[v]) {
            if (previous[w] == -1) {
                previous[w] = v;
                Q.push(w);
            }
        }
    }

    cout << "Yes" << LF;
    FOR(i, 1, N) { cout << previous[i]+1 << LF; }
}
