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
struct RangeAddRangeMinSegmentTree {
    int n;
    vector<Num> data;
    vector<Num> delayed;

    explicit RangeAddRangeMinSegmentTree(int size)
        : n(bit_ceil(size)), data(2*n-1), delayed(2*n-1) {}

    // [lo, hi) の区間の値に value を加算する
    void range_add(int lo, int hi, Num value) {
        range_add_(lo, hi, value, 0, 0, n);
    }

    // [lo, hi) の区間の min を返す
    Num range_min(int lo, int hi) {
        return range_min_(lo, hi, 0, 0, n);
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

    Num range_min_(int lo, int hi, int index, int left, int right) {
        force(index);
        if (hi <= left || right <= lo) { // この区間とクエリ区間が全く重ならないとき
            return numeric_limits<Num>::max();
        }
        if (lo <= left && right <= hi) { // この区間がクエリ区間に完全に包含されているとき
            return data[index];
        }
        // この区間の一部がクエリ区間とオーバーラップしているとき
        int middle = (left + right) / 2;
        Num v1 = range_min_(lo, hi, index*2+1, left, middle);
        Num v2 = range_min_(lo, hi, index*2+2, middle, right);
        return min(v1, v2);
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
