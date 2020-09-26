#include "lib/prelude.hpp"
#include "lib/io/string.hpp"
#include <atcoder/maxflow.hpp>

int main() {
    int N = read_int();
    int M = read_int();
    vector<string> field(N);
    REP(i, N) field[i] = read_word();

    atcoder::mf_graph<int> graph(N*M+2);
    int s = N*M, t = N*M+1;

    for(int y = 0; y < N; y += 2) {
        for(int x = 0; x < M; x += 2) {
            if (field[y][x] != '.') { continue; }
            static const int dy[] = {-1, 0, 1, 0};
            static const int dx[] = {0, -1, 0, 1};
            REP(k, 4) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || nx >= M || ny < 0 || ny >= N) { continue; }
                if (field[ny][nx] != '.') { continue; }
                graph.add_edge(y*M+x, ny*M+nx, 1);
            }
        }
    }
    REP(y, N) REP(x, M) if (field[y][x] == '.') {
        if ((y + x) % 2 == 0) {
            graph.add_edge(s, y*M+x, 1);
        } else {
            graph.add_edge(y*M+x, t, 1);
        }
    }

    auto ans = graph.flow(s, t);
    auto mincut = graph.min_cut(s);
    // TODO
    cout << ans << LF;
}
