#include "lib/prelude.hpp"
#include "lib/union_find.hpp"

int main() {
    int N = read_int();
    int M = read_int();
    int K = read_int();
    vector<vector<int>> friends(N);
    vector<vector<int>> blocks(N);
    UnionFind uf(N);
    REP(i, M) {
        int a = read_int()-1;
        int b = read_int()-1;
        friends[a].emplace_back(b);
        friends[b].emplace_back(a);
        uf.merge(a, b);
    }
    REP(i, K) {
        int c = read_int()-1;
        int d = read_int()-1;
        blocks[c].emplace_back(d);
        blocks[d].emplace_back(c);
    }

    REP(i, N) {
        int n_blocks = 0;
        for(int j : blocks[i]) {
            if (uf.same(i, j)) { n_blocks++; }
        }

        if (i != 0) cout << ' ';
        cout << (uf.size(i) - (int)friends[i].size() - n_blocks - 1);
    }
    cout << LF;
}
