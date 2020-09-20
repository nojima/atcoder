#pragma once
#include "std.hpp"

template <typename Traits>
auto monoid_pow(typename Traits::Monoid base, int exponent)
{
    using Monoid = typename Traits::Monoid;

    Monoid ans = Traits::identity();
    while (exponent > 0) {
        if (exponent & 1) {
            ans = Traits::op(ans, base);
        }
        base = Traits::op(base, base);
        exponent >>= 1;
    }
    return ans;
}

template <typename Traits>
auto monoid_concat(const vector<typename Traits::Monoid>& xs)
{
    using Monoid = typename Traits::Monoid;

    Monoid acc = Traits::identity();
    for (const auto& x : xs) {
        acc = Traits::op(acc, x);
    }
    return acc;
}

template <typename Traits>
auto cumulative(const vector<typename Traits::Monoid>& xs)
{
    using Monoid = typename Traits::Monoid;

    vector<Monoid> result;
    Monoid acc = Traits::identity();
    for (const auto& x : xs) {
        acc = Traits::op(acc, x);
        result.push_back(acc);
    }
    return result;
}

//-----------------------------------------------------------------------------
// モノイドの例

// 加算によるモノイド
struct SumMonoid {
    using Monoid = long long;

    static constexpr Monoid identity() {
        return 0;
    }

    static Monoid op(Monoid lhs, Monoid rhs) {
        return lhs + rhs;
    }
};

// 乗法によるモノイド
struct ProductMonoid {
    using Monoid = long long;

    static constexpr Monoid identity() {
        return 1;
    }

    static Monoid op(Monoid lhs, Monoid rhs) {
        return lhs * rhs;
    }
};

// MOD を法とする乗法によるモノイド
struct ModuloProductMonoid {
    using Monoid = long long;

    static constexpr Monoid identity() {
        return 1;
    }

    static Monoid op(Monoid lhs, Monoid rhs) {
        static const Monoid MOD = 1000000007;
        return (lhs * rhs) % MOD;
    }
};

// 文字列モノイド
struct StringMonoid {
    using Monoid = string;

    static Monoid identity() {
        return "";
    }

    static Monoid op(const Monoid& lhs, const Monoid& rhs) {
        return lhs + rhs;
    }
};

// TとUがそれぞれモノイドであるならば、pair<T, U> もモノイド
template <typename TraitsT, typename TraitsU>
struct PairMonoid {
    using Monoid = pair<typename TraitsT::Monoid, typename TraitsU::Monoid>;

    static constexpr Monoid identity() {
        return {
            TraitsT::identity(),
            TraitsU::identity(),
        };
    }

    static Monoid op(Monoid lhs, Monoid rhs) {
        return {
            TraitsT::op(lhs.first, rhs.first),
            TraitsU::op(lhs.second, rhs.second),
        };
    }
};

// Tがモノイドであるならば、optional<T> もモノイド
template <typename TraitsT>
struct OptionalMonoid {
    using Monoid = optional<typename TraitsT::Monoid>;

    static constexpr Monoid identity() {
        return nullopt;
    }

    static Monoid op(Monoid lhs, Monoid rhs) {
        if (!lhs && !rhs) { return nullopt; }
        if (!lhs) { return rhs; }
        if (!rhs) { return lhs; }
        return TraitsT::op(*lhs, *rhs);
    }
};
