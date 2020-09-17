#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/operators.hpp>
using namespace std;

constexpr int MOD = 1000000007;

// a を m で割った余り(>=0)を返す。
constexpr inline int mod(int a, int m) noexcept {
    int r = a % m;
    return r < 0 ? r + m : r;
}

struct ModInt : private boost::operators<ModInt> {
    int value;
    constexpr ModInt() noexcept : value(0) {}
    constexpr explicit ModInt(int value) noexcept
        : value(mod(value, MOD)) {}
    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {
        value += rhs.value;
        if (value > MOD) value -= MOD;
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {
        value -= rhs.value;
        if (value < 0) value += MOD;
        return *this;
    }
    constexpr ModInt& operator*=(const ModInt& rhs) noexcept {
        value = ((int64_t)value * rhs.value) % MOD;
        return *this;
    }
    constexpr bool operator<(const ModInt& rhs) const noexcept {
        return value < rhs.value;
    }
    constexpr bool operator==(const ModInt& rhs) const noexcept {
        return value == rhs.value;
    }
};
ostream& operator<<(ostream& os, const ModInt& rhs) {
    os << rhs.value;
    return os;
}
istream& operator>>(istream& is, ModInt& rhs) {
    int i; is >> i;
    rhs.value = mod(i, MOD);
    return is;
}
constexpr inline ModInt operator""_m(unsigned long long value) noexcept {
    return ModInt((int)value);
}

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int H, W; cin >> H >> W;
    vector field(H, vector(W, char()));
    REP(y, H) REP(x, W) cin >> field[y][x];

    // dp[y][x]: (0, 0)から(y, x)までの経路の数
    vector dp(H, vector(W, ModInt()));
    dp[0][0] = 1_m;
    REP(y, H) REP(x, W) {
        if(y+1 < H && field[y+1][x] == '.') dp[y+1][x] += dp[y][x];
        if(x+1 < W && field[y][x+1] == '.') dp[y][x+1] += dp[y][x];
    }

    cout << dp[H-1][W-1] << '\n';
}
