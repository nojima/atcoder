#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

template <typename Func>
vector<int64_t> make_cumsum(int n, Func get_ith_element) {
    vector<int64_t> cumsum(n+1);
    for (size_t i = 1; i < cumsum.size(); ++i) {
        cumsum[i] = cumsum[i-1] + get_ith_element(i-1);
    }
    return cumsum;
}

// [first, last] の和を返す
inline int64_t sum_of(const vector<int64_t>& cumsum, int first, int last) noexcept {
    return cumsum[last+1] - cumsum[first];
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int H, W, K; cin >> H >> W >> K;
    int start_y, start_x; cin >> start_y >> start_x; --start_y; --start_x;
    int goal_y, goal_x; cin >> goal_y >> goal_x; --goal_y; --goal_x;
    vector field(H, vector(W, char()));
    REP(y, H) REP(x, W) cin >> field[y][x];

    vector undet_v(W, set<int>()); // x座標 → その列の距離が未確定な頂点の集合
    vector undet_h(H, set<int>()); // y座標 → その行の距離が未確定な頂点の集合
    REP(x, W) REP(y, H) if (y != start_y || x != start_x) {
        undet_v[x].insert(y);
    }
    REP(y, H) REP(x, W) if (y != start_y || x != start_x) {
        undet_h[y].insert(x);
    }

    vector<vector<int64_t>> cumsum_v(W);
    vector<vector<int64_t>> cumsum_h(H);
    REP(x, W) cumsum_v[x] = make_cumsum(H, [x, &field](int y){ return field[y][x] == '@'; });
    REP(y, H) cumsum_h[y] = make_cumsum(W, [y, &field](int x){ return field[y][x] == '@'; });

    struct State { int y, x, d; };
    queue<State> Q;
    Q.push({start_y, start_x, 0});

    int ans = -1;
    while (!Q.empty()) {
        auto [y, x, d] = Q.front(); Q.pop();
        if (y == goal_y && x == goal_x) {
            ans = d;
            break;
        }
        // 下方向
        for (auto it = undet_v[x].lower_bound(y+1);
             it != undet_v[x].end(); ) {
            int ny = *it, nx = x;
            if (abs(ny - y) > K) break;
            if (sum_of(cumsum_v[x], min(y, ny), max(y, ny)) != 0) break;
            // (ny, nx)の距離は d+1 で確定
            it = undet_v[x].erase(it);
            undet_h[ny].erase(nx);
            Q.push({ny, nx, d+1});
        }
        // 上方向
        for (auto it = make_reverse_iterator(undet_v[x].upper_bound(y-1));
             it != undet_v[x].rend(); ) {
            int ny = *it, nx = x;
            if (abs(ny - y) > K) break;
            if (sum_of(cumsum_v[x], min(y, ny), max(y, ny)) != 0) break;
            // (ny, nx)の距離は d+1 で確定
            it = make_reverse_iterator(undet_v[x].erase(prev(it.base())));
            undet_h[ny].erase(nx);
            Q.push({ny, nx, d+1});
        }
        // 右方向
        for (auto it = undet_h[y].lower_bound(x+1);
             it != undet_h[y].end(); ) {
            int ny = y, nx = *it;
            if (abs(nx - x) > K) break;
            if (sum_of(cumsum_h[y], min(x, nx), max(x, nx)) != 0) break;
            // (ny, nx)の距離は d+1 で確定
            it = undet_h[y].erase(it);
            undet_v[nx].erase(ny);
            Q.push({ny, nx, d+1});
        }
        // 左方向
        for (auto it = make_reverse_iterator(undet_h[y].upper_bound(x-1));
             it != undet_h[y].rend(); ) {
            int ny = y, nx = *it;
            if (abs(nx - x) > K) break;
            if (sum_of(cumsum_h[y], min(x, nx), max(x, nx)) != 0) break;
            // (ny, nx)の距離は d+1 で確定
            it = make_reverse_iterator(undet_h[y].erase(prev(it.base())));
            undet_v[nx].erase(ny);
            Q.push({ny, nx, d+1});
        }
    }
    cout << ans << '\n';
}
