#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

struct Range { int left; int right; };

int main() {
    int H, W; cin >> H >> W;
    vector<Range> walls(H);
    REP(y, H) {
        int A, B; cin >> A >> B; --A; --B;
        walls[y] = { A, B };
    }

    set<pair<int, int>> end_and_starts;
    multiset<int> x_dists;

    REP(x, W) {
        end_and_starts.insert({x, x});
        x_dists.insert(0);
    }

    REP(y, H) {
        auto wall = walls[y];
        auto lo = end_and_starts.lower_bound({ wall.left, 0 });
        auto hi = end_and_starts.lower_bound({ wall.right+1, 0 });
        if (lo != hi) {
            int max_start = -1;
            for (auto it = lo; it != hi; ) {
                max_start = max(max_start, it->second);
                int x_dist = it->first - it->second;
                it = end_and_starts.erase(it);
                x_dists.erase(x_dists.find(x_dist));
            }
            if (wall.right != W-1) {
                int new_end = wall.right + 1;
                end_and_starts.insert({ new_end, max_start });
                x_dists.insert(new_end - max_start);
            }
        }
        if (x_dists.empty()) {
            cout << "-1\n";
        } else {
            int min_x_dist = *x_dists.begin();
            cout << min_x_dist + y + 1 << '\n';
        }
    }
}
