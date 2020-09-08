#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOREQ(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

static const int INF = 1e9;

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int H, W; cin >> H >> W;
    int start_y, start_x; cin >> start_y >> start_x;
    int goal_y, goal_x; cin >> goal_y >> goal_x;

    vector<vector<char>> field(H+2, vector<char>(W+2, '#'));
    FOREQ(y, 1, H) FOREQ(x, 1, W) cin >> field[y][x];

    deque<pair<int, int>> Q;
    vector<vector<int>> dist(H+2, vector<int>(W+2, INF));

    Q.emplace_back(start_y, start_x);
    dist[start_y][start_x] = 0;

    while (!Q.empty()) {
        auto [y, x] = Q.front(); Q.pop_front();
        if (y == goal_y && x == goal_x) {
            break;
        }
        static const int dy[] = {-1, 0, 1, 0};
        static const int dx[] = {0, -1, 0, 1};
        REP(i, 4) {
            int ny = y + dy[i], nx = x + dx[i];
            if (field[ny][nx] != '.') { continue; }

            int new_dist = dist[y][x];
            if (new_dist < dist[ny][nx]) {
                dist[ny][nx] = new_dist;
                Q.emplace_front(ny, nx);
            }
        }
        FOREQ(dy, -2, 2) {
            int ny = y + dy;
            if (ny < 0 || ny > H) { continue; }
            FOREQ(dx, -2, 2) {
                int nx = x + dx;
                if (nx < 0 || nx > W) { continue; }
                if (field[ny][nx] != '.') { continue; }

                int new_dist = dist[y][x] + 1;
                if (new_dist < dist[ny][nx]) {
                    dist[ny][nx] = new_dist;
                    Q.emplace_back(ny, nx);
                }
            }
        }
    }

    if (dist[goal_y][goal_x] < INF) {
        cout << dist[goal_y][goal_x] << '\n';
    } else {
        cout << -1 << '\n';
    }
}
