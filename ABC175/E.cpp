#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

template <typename T>
inline void assign_max(T& x, const T& value) {
    x = max(x, value);
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int R, C, K; cin >> R >> C >> K;
    map<pair<int, int>, int64_t> items;
    REP(i, K) {
        int r, c; int64_t v; cin >> r >> c >> v; --r; --c;
        items.insert({{r, c}, v});
    }

    vector dp(R+1, vector(C, vector(4, numeric_limits<int64_t>::min())));

    dp[0][0][0] = 0;
    REP(y, R+1) REP(x, C) REP(k, 4) {
        if (auto it = items.find({y, x}); k < 3 && it != items.end()) {
            // (y, x) にアイテムが存在し、拾うことが可能な場合
            int64_t value = it->second;
            if (y+1 < R+1)
                assign_max(dp[y+1][x][0], dp[y][x][k] + value);
            if (x+1 < C)
                assign_max(dp[y][x+1][k+1], dp[y][x][k] + value);
        }
        if (y+1 < R+1)
            assign_max(dp[y+1][x][0], dp[y][x][k]);
        if (x+1 < C)
            assign_max(dp[y][x+1][k], dp[y][x][k]);
    }

    cout << *max_element(ALL(dp[R][C-1])) << '\n';
}
