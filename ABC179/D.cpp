#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/operators.hpp>
using namespace std;

constexpr int MOD = 998244353;

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
#define ALL(c) (c).begin(), (c).end()

int bit_ceil(int n) {
    int ret = 1;
    while (ret < n) {
        ret *= 2;
    }
    return ret;
}

template <typename Num>
struct RangeAddSingleGetSegmentTree {
    int n;
    vector<Num> data;
    vector<Num> delayed;

    explicit RangeAddSingleGetSegmentTree(int size)
        : n(bit_ceil(size)), data(2*n-1), delayed(2*n-1) {}

    // [lo, hi) の区間の値に value を加算する
    void range_add(int lo, int hi, Num value) {
        range_add_(lo, hi, value, 0, 0, n);
    }

    Num get(int i) {
        return get_(i, 0, 0, n);
    }

private:
    void range_add_(int lo, int hi, Num value, int index, int left, int right) {
        force(index);
        if (hi <= left || right <= lo) { // この区間と更新区間が全く重ならないとき
            return;
        }
        if (lo <= left && right <= hi) { // この区間が更新区間に完全に包含されているとき
            data[index] += value;
            delayed[index] = value;
            return;
        }
        // この区間の一部が更新区間とオーバーラップしているとき
        int middle = (left + right) / 2;
        range_add_(lo, hi, value, index*2+1, left, middle);
        range_add_(lo, hi, value, index*2+2, middle, right);
        data[index] = min(data[index*2+1], data[index*2+2]);
    }

    Num get_(int i, int index, int left, int right) {
        force(index);
        if (left == i && right == i+1)
            return data[index];
        int middle = (left + right) / 2;
        if (left <= i && i < middle)
            return get_(i, index*2+1, left, middle);
        else
            return get_(i, index*2+2, middle, right);
    }

    void force(int index) {
        if (delayed[index] == Num(0)) return;
        if (index < n-1) {
            data[index*2+1] += delayed[index];
            data[index*2+2] += delayed[index];
            delayed[index*2+1] += delayed[index];
            delayed[index*2+2] += delayed[index];
        }
        delayed[index] = Num(0);
    }
};


int main() {
    int N, K; cin >> N >> K;
    vector<int> L(K), R(K);
    REP(i, K) cin >> L[i] >> R[i];

    RangeAddSingleGetSegmentTree<ModInt> dp(N);
    dp.range_add(0, 1, 1_m);
    REP(i, N) {
        auto v = dp.get(i);
        REP(k, K) {
            dp.range_add(min(L[k] + i, N),
                         min(R[k] + i + 1, N),
                         v);
        }
    }
    cout << dp.get(N-1) << '\n';
}
