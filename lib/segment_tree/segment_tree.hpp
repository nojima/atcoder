int bit_ceil(int n) {
    int ret = 1;
    while (ret < n) ret *= 2;
    return ret;
}

template<class T, class ProductFunc, class UpdateFunc>
struct LazySegmentTree {
    LazySegmentTree(
        int size,
        const T& identity,          // product(identity, x) = product(x, identity) = x
        const ProductFunc& product, // (T, T) -> T
        const UpdateFunc& update    // (T, T) -> T
    ): n(bit_ceil(size)), identity(identity), product(product), update(update),
       data(2*n-1, identity), delayed(2*n-1, nullopt) {}

    // [lo, hi) の区間のすべての要素を update(*, value) によって更新する
    void range_update(int lo, int hi, const T& value) {
        range_update_(lo, hi, value, 0, 0, n);
    }

    // [lo, hi) の区間のすべての要素の product による積を返す
    T range_query(int lo, int hi) {
        return range_query_(lo, hi, 0, 0, n);
    }

private:
    void range_update_(int lo, int hi, const T& value, int index, int left, int right) {
        force(index);
        if (hi <= left || right <= lo) { // この区間と更新区間が全く重ならないとき
            return;
        }
        if (lo <= left && right <= hi) { // この区間が更新区間に完全に包含されているとき
            data[index] = update(data[index], value);
            delayed[index] = value;
            return;
        }
        // この区間の一部が更新区間とオーバーラップしているとき
        int middle = (left + right) / 2;
        range_update_(lo, hi, value, index*2+1, left, middle);
        range_update_(lo, hi, value, index*2+2, middle, right);
        data[index] = product(data[index*2+1], data[index*2+2]);
    }

    T range_query_(int lo, int hi, int index, int left, int right) {
        force(index);
        if (hi <= left || right <= lo) { // この区間とクエリ区間が全く重ならないとき
            return identity;
        }
        if (lo <= left && right <= hi) { // この区間がクエリ区間に完全に包含されているとき
            return data[index];
        }
        // この区間の一部がクエリ区間とオーバーラップしているとき
        int middle = (left + right) / 2;
        T v1 = range_query_(lo, hi, index*2+1, left, middle);
        T v2 = range_query_(lo, hi, index*2+2, middle, right);
        return product(v1, v2);
    }

    void force(int index) {
        if (!delayed[index]) return;
        if (index < n-1) {
            force_child(index*2+1, *delayed[index]);
            force_child(index*2+2, *delayed[index]);
        }
        delayed[index] = nullopt;
    }

    void force_child(int index, const T& value) {
        data[index] = update(data[index], value);
        if (delayed[index])
            delayed[index] = update(*delayed[index], value);
        else
            delayed[index] = value;
    }

private:
    int n;
    T identity;
    ProductFunc product;
    UpdateFunc update;
    vector<T> data;
    vector<optional<T>> delayed;
};
