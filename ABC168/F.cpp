#include "lib/prelude.hpp"

// 区間[l, r]の列を受け取り、重複する区間をマージして返す。
template<class Int>
vector<pair<Int, Int>> merge_intervals(const vector<pair<Int, Int>>& intervals) {
    vector<pair<Int, bool>> events;
    for (auto [l, r] : intervals) {
        events.emplace_back(l, false);
        events.emplace_back(r, true);
    }
    sort(ALL(events));

    vector<pair<Int, Int>> ret;
    int current_intervals = 0;
    Int left = numeric_limits<Int>::min();
    for (auto [x, is_close_event] : events) {
        if (is_close_event) {
            --current_intervals;
            if (current_intervals == 0) { ret.emplace_back(left, x); }
        } else {
            if (current_intervals == 0) { left = x; }
            ++current_intervals;
        }
    }

    return ret;
}

vector<bool> intervals_to_bitmap(const vector<pair<int, int>>& intervals, int max_x) {
    vector<bool> bitmap(max_x+1);
    for(auto [x1, x2] : intervals) {
        for(int i = x1; i < x2; ++i) {
            bitmap[i] = true;
        }
    }
    return bitmap;
}

template<class Int>
int index_of(const vector<Int>& v, Int x) {
    auto it = lower_bound(ALL(v), x);
    return distance(v.begin(), it);
}

int main() {
    int N = read_int();
    int M = read_int();
    map<int, vector<pair<int, int>>> vertical_lines;
    REP(i, N) {
        int y1 = read_int();
        int y2 = read_int();
        int x = read_int();
        vertical_lines[x].emplace_back(y1, y2);
    }
    map<int, vector<pair<int, int>>> horizontal_lines;
    REP(i, M) {
        int y = read_int();
        int x1 = read_int();
        int x2 = read_int();
        horizontal_lines[y].emplace_back(x1, x2);
    }

    // 区間のマージ
    for (auto it = vertical_lines.begin(); it != vertical_lines.end(); ++it) {
        it->second = merge_intervals(it->second);
    }
    for (auto it = horizontal_lines.begin(); it != horizontal_lines.end(); ++it) {
        it->second = merge_intervals(it->second);
    }

    // 座標圧縮
    vector<int> xs = {0}, ys = {0};
    for (const auto& [x, segs] : vertical_lines) {
        xs.emplace_back(x);
        for (auto [y1, y2] : segs) {
            ys.emplace_back(y1);
            ys.emplace_back(y2);
        }
    }
    for (const auto& [y, segs] : horizontal_lines) {
        ys.emplace_back(y);
        for (auto [x1, x2] : segs) {
            xs.emplace_back(x1);
            xs.emplace_back(x2);
        }
    }
    sort(ALL(xs));
    xs.erase(unique(ALL(xs)), xs.end());
    sort(ALL(ys));
    ys.erase(unique(ALL(ys)), ys.end());

    vector v_map(xs.size()+1, vector(ys.size()+1, false));
    for (const auto& [x, segs] : vertical_lines) {
        int x_ = index_of(xs, x);
        auto segs_ = segs;
        REP(i, segs_.size()) {
            auto [a, b] = segs_[i];
            segs_[i] = {index_of(ys, a), index_of(ys, b)};
        }
        v_map[x_] = intervals_to_bitmap(segs_, ys.size());
    }
    vector h_map(ys.size()+1, vector(xs.size()+1, false));
    for (const auto& [y, segs] : horizontal_lines) {
        int y_ = index_of(ys, y);
        auto segs_ = segs;
        REP(i, segs_.size()) {
            auto [a, b] = segs_[i];
            segs_[i] = {index_of(xs, a), index_of(xs, b)};
        }
        h_map[y_] = intervals_to_bitmap(segs_, xs.size());
    }

    vector visited(ys.size()+1, vector(xs.size()+1, false));
    queue<pair<int, int>> Q;

    int origin_y = index_of(ys, 0);
    int origin_x = index_of(xs, 0);
    Q.push({origin_y, origin_x});
    visited[origin_y][origin_x] = true;
    int64_t ans = 0;
    bool is_inf = false;

    while (!Q.empty()) {
        auto [y, x] = Q.front(); Q.pop();
        // 現在、矩形 (y, x)-(y+1, x+1) の中にいる

        #define DOIT(yy, xx) {\
            if (xx < 0 || yy < 0 || xx >= (int)xs.size()-1 || yy >= (int)ys.size()-1) {\
                is_inf = true;\
                break;\
            }\
            if (!visited[yy][xx]) {\
                visited[yy][xx] = true;\
                Q.push({yy, xx});\
            }\
        }

        ans += int64_t(ys[y+1]-ys[y]) * int64_t(xs[x+1]-xs[x]);
        // 右に移動できるか: (y, x+1)-(y+1, x+1) がないなら可能
        if (!v_map[x+1][y]) { DOIT(y, x+1) }
        // 左に移動できるか: (y, x)-(y+1, x) がないなら可能
        if (!v_map[x][y]) { DOIT(y, x-1) }
        // 上に移動できるか: (y, x)-(y, x+1) がないなら可能
        if (!h_map[y][x]) { DOIT(y-1, x) }
        // 下に移動できるか: (y+1, x)-(y+1, x+1) がないなら可能
        if (!h_map[y+1][x]) { DOIT(y+1, x) }
    }

    if (is_inf) {
        cout << "INF" << LF;
    } else {
        cout << ans << LF;
    }
}
