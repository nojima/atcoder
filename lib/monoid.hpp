#pragma once
#include "std.hpp"

template<class T> struct Monoid;

template<class T>
auto monoid_pow(T base, int64_t exponent) {
    using M = Monoid<T>;
    T ans = M::identity();
    while (exponent > 0) {
        if (exponent & 1) {
            ans = M::op(ans, base);
        }
        base = M::op(base, base);
        exponent >>= 1;
    }
    return ans;
}

//-----------------------------------------------------------------------------
// モノイドの例

// 乗法によるモノイド
template<>
struct Monoid<int64_t> {
    static constexpr inline int64_t identity() noexcept { return 1; }
    static constexpr inline int64_t op(int64_t lhs, int64_t rhs) noexcept { return lhs * rhs; }
};

// 文字列モノイド
template<>
struct Monoid<string> {
    static inline string identity() { return ""; }
    static inline string op(const string& lhs, const string& rhs) { return lhs + rhs; }
};

// TとUがそれぞれモノイドであるならば、pair<T, U> もモノイド
template<typename T, typename U>
struct Monoid<pair<T, U>> {
    static inline pair<T, U> identity() {
        return { Monoid<T>::identity(), Monoid<U>::identity(), };
    }
    static inline pair<T, U> op(const pair<T, U>& lhs, const pair<T, U>& rhs) {
        return { Monoid<T>::op(lhs.first, rhs.first), Monoid<U>::op(lhs.second, rhs.second) };
    }
};

// Tがモノイドであるならば、optional<T> もモノイド
template<typename T>
struct Monoid<optional<T>> {
    static constexpr inline optional<T> identity() noexcept { return nullopt; }
    static optional<T> op(const optional<T>& lhs, const optional<T>& rhs) {
        if (!lhs && !rhs) { return nullopt; }
        if (!lhs) { return rhs; }
        if (!rhs) { return lhs; }
        return Monoid<T>::op(*lhs, *rhs);
    }
};
