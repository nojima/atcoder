#include "lib/prelude.hpp"
#include "lib/fix.hpp"

int main() {
    int N = read_int();
    int M = read_int();
    vector<vector<int>> graph(N);
    REP(i, M) {
        int a = read_int() - 1;
        int b = read_int() - 1;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }

    vector<bool> visited(N);
    auto dfs = Fix([&](auto&& self, int v) -> void {
        if (visited[v]) return;
        visited[v] = true;
        for(auto dst : graph[v]) {
            self(dst);
        }
    });

    int cc = 0;
    REP(i, N) {
        if (!visited[i]) {
            dfs(i);
            ++cc;
        }
    }
    cout << cc-1 << endl;
}
