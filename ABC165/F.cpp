#include "lib/prelude.hpp"
#include "lib/bit.hpp"
#include "lib/binary_search.hpp"
#include "lib/persistent_array.hpp"

int N;
vector<int64_t> A;
vector<vector<int>> graph;
vector<int> ans;

void dp(int v, int len, PersistentArray<int> lis) {
    if (ans[v] != -1) return;
    int ll = find_minimum_solution(0, N+1, [&lis, a=A[v]](int l){
        return a < lis.get(l);
    });
    if (ll >= 1 && lis.get(ll-1) < A[v]) {
        lis = lis.set(ll, A[v]);
    }
    ans[v] = find_maximum_solution(0, N, [&lis](int l){
        return lis.get(l) < numeric_limits<int>::max();
    });
    for (int w : graph[v]) {
        dp(w, len+1, lis);
    }
}

int main() {
    N = read_int();
    A.resize(N);
    REP(i, N) A[i] = read_int();
    graph.resize(N);
    REP(i, N-1) {
        int u = read_int()-1;
        int v = read_int()-1;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    ans.resize(N);
    fill(ALL(ans), -1);

    // lis[l]: 長さ l の最長増加部分列の高さの最小値
    PersistentArray lis(N+1, numeric_limits<int>::max());
    lis = lis.set(0, 0);
    dp(0, 1, lis);

    REP(i, N) cout << ans[i] << LF;
}
