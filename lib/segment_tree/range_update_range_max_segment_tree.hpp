#include <vector>
#include <algorithm>
#include <limits>

int bit_ceil(int n) {
    int ret = 1;
    while (ret < n) {
        ret *= 2;
    }
    return ret;
}

template <typename Num>
struct RangeUpdateRangeMaxSegmentTree {
    int n;
    vector<Num> data;
    vector<bool> delayed;

    explicit RangeUpdateRangeMaxSegmentTree(int size)
        : n(bit_ceil(size)), data(2*n-1), delayed(2*n-1) {}

    // [lo, hi) の区間の値を value に更新する
    void range_update(int lo, int hi, Num value) {
        range_update_(lo, hi, value, 0, 0, n);
    }

    // [lo, hi) の区間の max を返す
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
            delayed[index] = true;
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
        if (!delayed[index]) return;
        if (index < n-1) {
            data[index*2+1] = data[index];
            data[index*2+2] = data[index];
            delayed[index*2+1] = true;
            delayed[index*2+2] = true;
        }
        delayed[index] = false;
    }
};
