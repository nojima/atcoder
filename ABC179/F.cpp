#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

template <typename T> inline void assign_min(T& x, const T& value) noexcept { x = min(x, value); }
template <typename T> inline void assign_max(T& x, const T& value) noexcept { x = max(x, value); }

int bit_ceil(int n) {
    int ret = 1;
    while (ret < n) {
        ret *= 2;
    }
    return ret;
}

template <typename Num>
struct RangeMinSegmentTree {
    int n;
    vector<Num> data;
    vector<Num> delayed;

    explicit RangeMinSegmentTree(int size)
        : n(bit_ceil(size)), data(2*n-1), delayed(2*n-1) {}

    // [lo, hi) の区間の値を min で更新する
    void range_update(int lo, int hi, Num value) {
        range_update_(lo, hi, value, 0, 0, n);
    }

    void update(int i, Num value) {
        range_update(i, i+1, value);
    }

    // [lo, hi) の区間の min を返す
    Num range_max(int lo, int hi) {
        return range_max_(lo, hi, 0, 0, n);
    }

private:
    void range_update_(int lo, int hi, Num value, int index, int left, int right) {
        force(index);
        if (hi <= left || right <= lo) { // この区間と更新区間が全く重ならないとき
            return;
        }
        if (lo <= left && right <= hi) { // この区間が更新区間に完全に包含されているとき
            data[index] = value;
            delayed[index] = value;
            return;
        }
        // この区間の一部が更新区間とオーバーラップしているとき
        int middle = (left + right) / 2;
        range_update_(lo, hi, value, index*2+1, left, middle);
        range_update_(lo, hi, value, index*2+2, middle, right);
        data[index] = max(data[index*2+1], data[index*2+2]);
    }

    Num range_max_(int lo, int hi, int index, int left, int right) {
        force(index);
        if (hi <= left || right <= lo) { // この区間とクエリ区間が全く重ならないとき
            return numeric_limits<Num>::min();
        }
        if (lo <= left && right <= hi) { // この区間がクエリ区間に完全に包含されているとき
            return data[index];
        }
        // この区間の一部がクエリ区間とオーバーラップしているとき
        int middle = (left + right) / 2;
        Num v1 = range_max_(lo, hi, index*2+1, left, middle);
        Num v2 = range_max_(lo, hi, index*2+2, middle, right);
        return max(v1, v2);
    }

    void force(int index) {
        if (delayed[index] == 0) return;
        if (index < n-1) {
            data[index*2+1] = delayed[index];
            data[index*2+2] = delayed[index];
            delayed[index*2+1] = delayed[index];
            delayed[index*2+2] = delayed[index];
        }
        delayed[index] = 0;
    }
};

// 区間[a, b)の中で最初に pred(x) = true となるような x を返す。
// そのような x が存在しないときは b を返す。
template <class Pred>
int64_t bin_search(int64_t a, int64_t b, Pred pred) {
    // 不変条件: i<a ⇒ pred(i)=false, i>=b ⇒ pred(i)=true
    if (a == b) return b;
    int64_t m = a + (b - a) / 2;
    if (pred(m))
        return bin_search(a, m, pred);
    else
        return bin_search(m+1, b, pred);
}

int main() {
    int64_t N, Q; cin >> N >> Q;
    N -= 2;
    RangeMinSegmentTree<int> vertical(N+1);
    RangeMinSegmentTree<int> horizontal(N+1);
    int64_t ans = 0;
    REP(i, Q) {
        int a, x; cin >> a >> x; --x;
        if (a == 1) {
            auto K = bin_search(1, N+1, [&](int k) {
                return !(horizontal.range_max(1, k+1) < x);
            });
            vertical.update(x, K);
            ans += K-1;
        } else {
            auto K = bin_search(1, N+1, [&](int k) {
                return !(vertical.range_max(1, k+1) < x);
            });
            horizontal.update(x, K);
            ans += K-1;
        }
    }
    cout << N*N - ans << endl;
}
