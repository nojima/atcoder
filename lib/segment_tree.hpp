#pragma once
#include "lib/bit.hpp"

template<class T, class Product>
struct SegmentTree {
    SegmentTree(int size, const T& identity, const Product& product)
        : n(bit_ceil(size)), data(2*n-1, identity), identity(identity), product(product) {}
    T get(int i) const { return data[n+i-1]; }
    T prod(int l, int r) const { return prod(l, r, 0, 0, n); }
    void set(int i, const T& x) { set(i, x, 0, 0, n); }

private:
    T prod(int l, int r, int v, int nl, int nr) const {
        if (r <= nl || nr <= l) { return identity; }
        if (l <= nl && nr <= r) { return data[v]; }
        int nm = (nl + nr) / 2;
        auto x1 = prod(l, r, 2*v+1, nl, nm);
        auto x2 = prod(l, r, 2*v+2, nm, nr);
        return product(x1, x2);
    }

    void set(int i, const T& x, int v, int nl, int nr) {
        assert(nl <= i && i < nr);
        if (nl == i && nr == i+1) {
            data[v] = x;
        } else {
            int nm = (nl + nr) / 2;
            if (i < nm) { set(i, x, 2*v+1, nl, nm); }
            else        { set(i, x, 2*v+2, nm, nr); }
            data[v] = product(data[2*v+1], data[2*v+2]);
        }
    }

private:
    int n;
    vector<T> data;
    T identity;
    Product product;
};
