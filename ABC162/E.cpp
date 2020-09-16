#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/operators.hpp>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

constexpr int MOD = 1000000007;

// ax + by = gcd(a, b) を満たすような整数 x,y を返す。
pair<int64_t, int64_t> exgcd(int a, int b) noexcept {
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a%b);
    return {y, x-(a/b)*y};
}

// a を m で割った余り(>=0)を返す。
constexpr inline int mod(int a, int m) noexcept {
    int r = a % m;
    return r < 0 ? r + m : r;
}

// a の逆元を返す。a は MOD と互いに素でなければならない。
inline int inverse(int a) noexcept {
    return mod(exgcd(MOD, a).second, MOD);
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
    ModInt& operator/=(const ModInt& rhs) noexcept {
        value = ((int64_t)value * inverse(rhs.value)) % MOD;
        return *this;
    }
    constexpr bool operator<(const ModInt& rhs) noexcept {
        return value < rhs.value;
    }
    constexpr bool operator==(const ModInt& rhs) noexcept {
        return value == rhs.value;
    }
};
ostream& operator<<(ostream& os, ModInt& rhs) {
    os << rhs.value;
    return os;
}
istream& operator>>(istream& is, ModInt& rhs) {
    int i; is >> i;
    rhs.value = mod(i, MOD);
    return is;
}
constexpr ModInt operator""_m(unsigned long long value) noexcept {
    return ModInt((int)value);
}

ModInt pow_mod(ModInt n, int64_t p) {
    ModInt ans = 1_m;
    while (p > 0) {
        if (p & 1) ans *= n;
        n *= n;
        p >>= 1;
    }
    return ans;
}

int main() {
    int N, K; cin >> N >> K;

    // g(i): gcd(A_1,..,A_N) = i となるような {A_1,..,A_N} の数
    vector<ModInt> g(K+1);

    for (int i = K; i > 0; --i) {
        ModInt k = pow_mod(ModInt(K/i), N);
        for (int j = 2; i*j <= K; ++j) {
            k -= g[i*j];
        }
        g[i] = k;
    }

    ModInt ans = 0_m;
    for (int i = 1; i <= K; ++i)
        ans += g[i] * ModInt(i);
    cout << ans << '\n';
}
