#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

inline bool test_bit(unsigned S, int i) {
    return (i >= 0) ? ((S >> i) & 1) : false;
}

int best_splits(
    const vector<vector<bool>>& choco,
    int H, int W, int K,
    unsigned S
) {
    vector<int> group(H);
    int current_group = 0;
    REP(y, H) {
        if (test_bit(S, y-1)) { current_group++; }
        group[y] = current_group;
    }
    int group_count = current_group + 1;
    vector<int> n_whites(group_count);

    int v_splits = 0;
    REP(x, W) {
        REP(y, H) if (choco[y][x]) {
            n_whites[group[y]]++;
        }
        bool should_split = any_of(ALL(n_whites), [K](int n) { return n > K; });
        if (should_split) {
            v_splits++;
            fill(ALL(n_whites), 0);
            REP(y, H) if (choco[y][x]) {
                n_whites[group[y]]++;
            }
            bool impossible = any_of(ALL(n_whites), [K](int n) { return n > K; });
            if (impossible) {
                return numeric_limits<int>::max();
            }
        }
    }

    return __builtin_popcount(S) + v_splits;
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int H, W, K; cin >> H >> W >> K;
    vector<vector<bool>> choco(H, vector<bool>(W));
    REP(y, H) REP(x, W) {
        char s; cin >> s;
        choco[y][x] = s == '1';
    }

    int ans = numeric_limits<int>::max();
    for (unsigned S = 0; S < (unsigned)(1 << (H-1)); ++S) {
        int n_splits = best_splits(choco, H, W, K, S);
        ans = min(ans, n_splits);
    }
    cout << ans << '\n';
}
