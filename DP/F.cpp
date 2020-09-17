#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

template <typename T, typename U>
inline void assign_max(T& x, U& y, const T& value1, const U& value2) noexcept {
    if (x < value1) {
        x = value1;
        y = value2;
    }
}

int main() {
    string s, t; cin >> s >> t;

    enum class Choice { NONE, PICK, SHIFT_S, SHIFT_T };

    // dp[i][j]: s[0..i], t[0..j] の部分列の長さの最大値
    vector dp(s.size(), vector(t.size(), int()));
    vector choice(s.size(), vector(t.size(), Choice()));

    REP(i, s.size()) REP(j, t.size()) {
        int m = 0;
        Choice c = Choice::NONE;
        if (s[i] == t[j]) {
            if (i > 0 && j > 0) {
                assign_max(m, c, dp[i-1][j-1] + 1, Choice::PICK);
            } else {
                assign_max(m, c, 1, Choice::PICK);
            }
        }
        if (i > 0) {
            assign_max(m, c, dp[i-1][j], Choice::SHIFT_S);
        }
        if (j > 0) {
            assign_max(m, c, dp[i][j-1], Choice::SHIFT_T);
        }
        dp[i][j] = m;
        choice[i][j] = c;
    }

    // 復元
    string ans;
    for ( int i = s.size()-1, j = t.size()-1
        ; i >= 0 && j >= 0
        ;
    ) {
        switch (choice[i][j])
        {
        case Choice::NONE:
            --i; --j;
            break;
        case Choice::PICK:
            ans += s[i];
            --i; --j;
            break;
        case Choice::SHIFT_S:
            --i; break;
        case Choice::SHIFT_T:
            --j; break;
        }
    }
    reverse(ALL(ans));

    cout << ans << '\n';
}
