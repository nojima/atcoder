template <typename Monoid>
struct MonoidTraits;

// モノイドの冪乗を求める
template <typename Monoid>
Monoid monoid_pow(Monoid base, int exponent) {
    using M = MonoidTraits<Monoid>;

    Monoid ans = M::identity();
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

// MOD を法とする乗法によるモノイド
template <>
struct MonoidTraits<long long> {
    static const long long MOD = 1000000007;

    static long long identity() {
        return 1;
    }

    static long long op(long long lhs, long long rhs) {
        return (lhs * rhs) % MOD;
    }
};

// 文字列モノイド
template <>
struct MonoidTraits<string> {
    static string identity() {
        return "";
    }

    static string op(const string& lhs, const string& rhs) {
        return lhs + rhs;
    }
};

// TとUがそれぞれモノイドであるならば、pair<T, U> もモノイド
template <typename T, typename U>
struct MonoidTraits<pair<T, U>> {
    static pair<T, U> identity() {
        return {
            MonoidTraits<T>::identity(),
            MonoidTraits<U>::identity(),
        };
    }

    static pair<T, U> op(pair<T, U> lhs, pair<T, U> rhs) {
        return {
            MonoidTraits<T>::op(lhs.first, rhs.first),
            MonoidTraits<U>::op(lhs.second, rhs.second),
        };
    }
};
