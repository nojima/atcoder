#pragma once
#include "std.hpp"
#include <boost/operators.hpp>

// a を m で割った余り(>=0)を返す。
constexpr inline int mod(int a, int m) noexcept {
    int r = a % m;
    return r < 0 ? r + m : r;
}

// ax + by = gcd(a, b) を満たすような整数 x,y を返す。
template<int MOD>
pair<int64_t, int64_t> exgcd(int a, int b) noexcept {
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd<MOD>(b, a%b);
    return {y, x-(a/b)*y};
}

// a の逆元を返す。a は MOD と互いに素でなければならない。
template<int MOD>
inline int inverse(int a) noexcept {
    return mod(exgcd<MOD>(MOD, a).second, MOD);
}

template<int MOD>
struct ModInt : private boost::operators<ModInt<MOD>> {
    int value;
    constexpr ModInt() noexcept : value(0) {}
    constexpr explicit ModInt(int value) noexcept
        : value(mod(value, MOD)) {}
    constexpr ModInt<MOD>& operator+=(const ModInt<MOD>& rhs) noexcept {
        value += rhs.value;
        if (value > MOD) value -= MOD;
        return *this;
    }
    constexpr ModInt<MOD>& operator-=(const ModInt<MOD>& rhs) noexcept {
        value -= rhs.value;
        if (value < 0) value += MOD;
        return *this;
    }
    constexpr ModInt<MOD>& operator*=(const ModInt<MOD>& rhs) noexcept {
        value = ((int64_t)value * rhs.value) % MOD;
        return *this;
    }
    ModInt<MOD>& operator/=(const ModInt<MOD>& rhs) noexcept {
        value = ((int64_t)value * inverse<MOD>(rhs.value)) % MOD;
        return *this;
    }
    constexpr bool operator<(const ModInt<MOD>& rhs) const noexcept {
        return value < rhs.value;
    }
    constexpr bool operator==(const ModInt<MOD>& rhs) const noexcept {
        return value == rhs.value;
    }
};
template<int MOD>
ostream& operator<<(ostream& os, const ModInt<MOD>& rhs) {
    os << rhs.value;
    return os;
}
template<int MOD>
istream& operator>>(istream& is, ModInt<MOD>& rhs) {
    int i; is >> i;
    rhs.value = mod(i, MOD);
    return is;
}

// a^n を返す。
template<int MOD>
ModInt<MOD> pow_mod(ModInt<MOD> a, int64_t n) {
    auto ans = ModInt<MOD>(1);
    while (n > 0) {
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}
