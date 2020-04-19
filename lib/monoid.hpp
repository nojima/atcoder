template <typename T>
struct MonoidTrait {
    MonoidTrait() = delete;
};

/*
Example:

template <>
struct MonoidTrait<long long> {
    static const long long MOD = 1000000007;

    static long long identity() {
        return 1;
    }

    static int op(long long lhs, long long rhs) {
        return (lhs * rhs) % MOD;
    }
};
*/

// モノイドの冪乗を求める
template <typename Monoid>
Monoid monoid_pow(Monoid base, int exponent) {
    using M = MonoidTrait<Monoid>;

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
