// モノイドの冪乗を求める
template <typename Traits, typename Monoid>
Monoid monoid_pow(Monoid base, int exponent) {
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

//-----------------------------------------------------------------------------
// モノイドの例

// 加算によるモノイド
struct SumMonoid {
    using ValueType = long long;

    static constexpr ValueType identity() {
        return 0;
    }

    static ValueType op(ValueType lhs, ValueType rhs) {
        return lhs + rhs;
    }
};

// 乗法によるモノイド
struct ProductMonoid {
    using ValueType = long long;

    static constexpr ValueType identity() {
        return 1;
    }

    static ValueType op(ValueType lhs, ValueType rhs) {
        return lhs * rhs;
    }
};

// MOD を法とする乗法によるモノイド
struct ModuloProductMonoid {
    using ValueType = long long;

    static constexpr ValueType identity() {
        return 1;
    }

    static ValueType op(ValueType lhs, ValueType rhs) {
        static const ValueType MOD = 1000000007;
        return (lhs * rhs) % MOD;
    }
};

// 文字列モノイド
struct StringMonoid {
    using ValueType = string;

    static ValueType identity() {
        return "";
    }

    static ValueType op(const ValueType& lhs, const ValueType& rhs) {
        return lhs + rhs;
    }
};

// TとUがそれぞれモノイドであるならば、pair<T, U> もモノイド
template <typename TraitsT, typename TraitsU>
struct PairMonoid {
    using ValueType = pair<typename TraitsT::ValueType, typename TraitsU::ValueType>;

    static constexpr ValueType identity() {
        return {
            TraitsT::identity(),
            TraitsU::identity(),
        };
    }

    static ValueType op(ValueType lhs, ValueType rhs) {
        return {
            TraitsT::op(lhs.first, rhs.first),
            TraitsU::op(lhs.second, rhs.second),
        };
    }
};
