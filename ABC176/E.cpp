#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

template <class C, class T> inline bool contains(const C& c, const T& x) { return c.find(x) != c.end(); }

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int H, W, M; cin >> H >> W >> M;
    set<pair<int, int>> targets;
    REP(i, M) {
        int h, w; cin >> h >> w; --h; --w;
        targets.emplace(h, w);
    }

    vector<int> vertical_counts(W);
    for (auto [y, x] : targets) {
        ++vertical_counts[x];
    }
    int v_max = *max_element(ALL(vertical_counts));
    vector<int> max_cols;
    REP(x, W) {
        if (vertical_counts[x] == v_max)
            max_cols.push_back(x);
    }

    vector<int> horizontal_counts(H);
    for (auto [y, x] : targets) {
        ++horizontal_counts[y];
    }
    int h_max = *max_element(ALL(horizontal_counts));
    vector<int> max_rows;
    REP(y, H) {
        if (horizontal_counts[y] == h_max)
            max_rows.push_back(y);
    }

    if (max_rows.size() * max_cols.size() > (size_t)M) {
        cout << v_max + h_max << '\n';
    } else {
        bool found =
            any_of(ALL(max_rows), [&](int r) {
                return any_of(ALL(max_cols), [&](int c) {
                    return !contains(targets, make_pair(r, c));
                });
            });
        int ans = v_max + h_max - (found ? 0 : 1);
        cout << ans << '\n';
    }
}
